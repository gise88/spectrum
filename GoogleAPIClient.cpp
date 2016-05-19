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
#include "Request.h"
#include "Exceptions.h"

#include "SpectrumConstants.h"
#include "GoogleAPIClient.h"




static std::string readGoogleSpectrumApiKeyFromFile() {
	std::ifstream infile(GOOGLE_SPECTRUM_API_KEY_FILE);
	std::string apiKey;

	if (infile.good())
		getline(infile, apiKey);
	else {
		LogE("The file \"" GOOGLE_SPECTRUM_API_KEY_FILE "\" has not been found!\nYou have to create it with the only Google Spectrum Key.");
		exit(1);
	}
	
	infile.close();
	return apiKey;
}

// initialize static members in the GoogleAPIClient class
unsigned int GoogleAPIClient::m_request_count = 0;
std::string GoogleAPIClient::m_google_spectrum_api_key = readGoogleSpectrumApiKeyFromFile();


JSON GoogleAPIClient::PostAPI(double latitude, double longitude, double antenna_height) {

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
							}}
					}},
				{"antenna",
					{
						{"height", antenna_height},
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
							JSON::object()}
					}},
				{"key", GoogleAPIClient::m_google_spectrum_api_key}
			}},
		{"id", std::string("SpectrumRequestNumber-").append(std::to_string(GoogleAPIClient::m_request_count++))}
	};

	return req.PostJSON(data);
}