/*
 * Copyright (C) 2016 Gianluca Iselli <gianluca.iselli@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <fstream>

#include "Log.h"
#include "Utilities.h"
#include "Request.h"
#include "SpectrumConstants.h"
#include "GoogleAPIClient.h"



static std::string readGoogleSpectrumApiKeyFromFile() {
	LogD(0, "readGoogleSpectrumApiKeyFromFile()\n");
	
	std::ifstream infile(GOOGLE_SPECTRUM_API_KEY_FILE);
	std::string apiKey;

	if (infile.good())
		getline(infile, apiKey);
	else
		DieWithError(1, "The file \"" GOOGLE_SPECTRUM_API_KEY_FILE "\" has not been found!\nYou have to create it with the only Google Spectrum Key.");
	
	infile.close();
	return apiKey;
}

// initialize static members in the GoogleAPIClient class
unsigned int GoogleAPIClient::m_RequestCount = 0;
std::string GoogleAPIClient::m_GoogleSpectrumAPIKey = readGoogleSpectrumApiKeyFromFile();


GoogleAPIClient::GoogleAPIClient() {
	LogD(0, "GoogleAPIClient()\n");
	m_AntennaHeight = DEFAULT_ANTENNA_HEIGHT;
	m_DeviceType = DEFAULT_DEVICE_TYPE;
}

GoogleAPIClient::GoogleAPIClient(double meters, DeviceType type) {
	LogD(0, "GoogleAPIClient(%lf, %s)\n", meters, type._to_string());
	
	m_AntennaHeight = meters;
	switch (type) {
		case DeviceType::FIXED:
			m_DeviceType = DEVICE_TYPE_FIXED;
			break;
		case DeviceType::MODE_1:
			m_DeviceType = DEVICE_TYPE_MODE_1;
			break;
		case DeviceType::MODE_2:
			m_DeviceType = DEVICE_TYPE_MODE_2;
			break;
	}
}

GoogleAPIClient::~GoogleAPIClient() {
	LogD(0, "~GoogleAPIClient()\n");
}

std::string GoogleAPIClient::GetCurrentConfiguration() {
	return m_DeviceType + "_" + std::to_string(m_AntennaHeight);
}

std::vector<SpectrumChannel> GoogleAPIClient::GetSpectrumChannels(double latitude, double longitude) {
	LogD(0, "GetSpectrumChannels(%lf, %lf)\n", latitude, longitude);
	
	// from: https://developers.google.com/spectrum/paws/gettingstarted#try-out-google-spectrum-database
	Request req(GOOGLE_SPECTRUM_API_URL);
	req.SetTimeout(10);
	
	JSON data = {
		{"jsonrpc", "2.0"},
		{"method", "spectrum.paws.getSpectrum"},
		{"apiVersion", "v1explorer"},
		{"params",
			{
				{"type", "AVAIL_SPECTRUM_REQ"},
				{"version", "1.0"},
				{"deviceDesc",
					{
						{"serialNumber", "your_serial_number"},
						{"fccId", "TEST"},
						{"fccTvbdDeviceType", "MODE_1"}
					}},
				{"location",
					{
						{ "point",
							{
								{ "center",
									{
										{"latitude", latitude},
										{"longitude", longitude}
									}}
							}}}},
				{"antenna",
					{
						{"height", m_AntennaHeight},
						{"heightType", "AGL"}
					}},
				{"capabilities",
					{
						{"frequencyRanges",
//							{
//								{
//									{"startHz", 800000000},
//									{"stopHz", 850000000}
//								},
//								{
//									{"startHz", 900000000},
//									{"stopHz", 950000000}
//								}
//							}
							JSON::object()
						}
					}},
				{"key", GoogleAPIClient::m_GoogleSpectrumAPIKey}
			}},
		{"id", std::string("SpectrumRequestNumber-").append(std::to_string(GoogleAPIClient::m_RequestCount++))}
	};

	return JSONSpectrum2SpectrumChannels(req.PostJSON(data));
}

std::vector<SpectrumChannel> GoogleAPIClient::JSONSpectrum2SpectrumChannels(JSON&& res) {
	LogD(0, "JSONSpectrum2SpectrumChannels(JSON&& res)\n");
	
	std::vector<SpectrumChannel> channels;
	
	if (!res["error"].empty())
		throw MakeException(JsonWithErrorException,  "Error code: " +std::to_string(res["error"]["code"].get<int>()) + "   Error message:" + res["error"]["message"].get<std::string>());
		
	JSON spectra0 = res["result"]["spectrumSchedules"][0]["spectra"][0];	
	double bandwidth = spectra0["bandwidth"].get<double>();	
	LogD(1, "bandwidth: %.2lf\n", bandwidth);	
	
	uint channel_nr=FIRST_CHANNEL_AVAILABLE;
	LogD(1, "frequencyRanges:\n");
	for (auto freq_range : spectra0["frequencyRanges"]) {
		uint startHz = freq_range["startHz"].get<uint>();
		uint stopHz = freq_range["stopHz"].get<uint>();
		double maxPowerDBm = freq_range["maxPowerDBm"].get<double>();
		
		if (startHz < FIRST_CHANNEL_AVAILABLE_HZ)
			startHz = FIRST_CHANNEL_AVAILABLE_HZ;
		
		LogD(1, "startHz: %d  stopHz: %d  maxPowerDBm: %.12lf\n", startHz, stopHz, maxPowerDBm);
		
		for (; startHz < stopHz; startHz += bandwidth) {
			LogD(1, "ch#%d  -  startHz: %d  stopHz: %d  maxPowerDBm: %.12lf\n",channel_nr, startHz, (uint)(startHz+bandwidth), maxPowerDBm);
			channels.push_back(SpectrumChannel(channel_nr, maxPowerDBm));
			channel_nr++;
		}
		
	}
	LogD(2, "# channels: %d\n", channel_nr);
	
	return channels;
}