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


#include "Log.h"
#include "Exceptions.h"
#include "SpectrumManager.h"
#include "SpectrumConstants.h"
#include "GoogleAPIClient.h"
#include "SpectrumChannelsCacheFactory.h"


SpectrumManager::SpectrumManager(double SW_lat, double SW_lon, double area_width, double area_height, double cell_side_size, bool use_cache)
: m_UseCache(use_cache), m_ProjectionMapper(SW_lat, SW_lon, area_width, area_height, cell_side_size), m_ChannelsCache(nullptr) {
	LogD(0, "SpectrumManager(%lf, %lf, %.2lf, %.2lf, %.2lf, %s)\n", SW_lat, SW_lon, area_width, area_height, cell_side_size, use_cache ? "true" : "false");
	if (m_UseCache)
		m_ChannelsCache = SpectrumChannelsCacheFactory::CreateSpectrumChannelsCache(SW_lat, SW_lon, area_width, area_height, cell_side_size);
}

SpectrumManager::~SpectrumManager() {
	LogD(0, "~SpectrumManager()\n");
	
	delete m_ChannelsCache;
}

const std::vector<SpectrumChannel> SpectrumManager::GetChannels(uint pos_x, uint pos_y, double antenna_height) {
	LogD(0, "GetChannels(%d, %d, %lf)\n", pos_x, pos_y, antenna_height);
	
	uint x, y;
	double lat, lng;
	std::vector<SpectrumChannel> cache;
	
	if (m_UseCache) {
		m_ProjectionMapper.LocalPosXY2IndexXY(pos_x, pos_y, x, y);
		cache = m_ChannelsCache->get(x, y);
		if (cache.size() > 0) {
			LogD(2, "m_ChannelsCache->get(x: %d, y: %d)\n", x, y);
			return cache;
		}
	}
	
	
	// convert the JSON result into the vector of SpectrumChannel, 
	// push the new informations into the cache and return these values
	
	m_ProjectionMapper.LocalPosXY2LatLng(pos_x, pos_y, lat, lng);
	LogL(5, "GoogleAPIClient::PostAPI(lat: %lf, lng: %lf)\n", lat, lng);
	JSON res = GoogleAPIClient::PostAPI(lat, lng, antenna_height);
	cache = JSONSpectrum2SpectrumChannels(res);
	
	if (m_UseCache)
		m_ChannelsCache->push(x, y, cache);
	
	return cache;
}

std::vector<SpectrumChannel> SpectrumManager::JSONSpectrum2SpectrumChannels(JSON& res) {
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