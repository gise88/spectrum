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
: m_UseCache(use_cache), m_ProjectionMapper(SW_lat, SW_lon, area_width, area_height, cell_side_size), m_ChannelsRAMCache(nullptr) {
	LogD(0, "SpectrumManager(%lf, %lf, %.2lf, %.2lf, %.2lf, %s)\n", SW_lat, SW_lon, area_width, area_height, cell_side_size, use_cache ? "true" : "false");
	if (m_UseCache)
		m_ChannelsRAMCache = SpectrumChannelsCacheFactory::CreateSpectrumChannelsRAMCache(SW_lat, SW_lon, area_width, area_height, cell_side_size);
}

SpectrumManager::~SpectrumManager() {
	LogD(0, "~SpectrumManager()\n");
	
	if (m_UseCache)
		delete m_ChannelsRAMCache;
}

void SpectrumManager::SetASpectrumApiClient(std::unique_ptr<ASpectrumApiClient>&& api_client) {
	LogD(0, "SetASpectrumApiClient(*api_client*)\n");
	m_ApiClient = std::move(api_client);
	
	if (m_UseCache)
		m_ChannelsRAMCache->ClearCache();
}

const std::vector<SpectrumChannel> SpectrumManager::GetChannels(uint pos_x, uint pos_y) {
	LogD(0, "GetChannels(%d, %d)\n", pos_x, pos_y);
	
	uint x, y;
	double lat, lng;
	std::vector<SpectrumChannel> cache;
	
	if (m_UseCache) {
		m_ProjectionMapper.LocalPosXY2IndexXY(pos_x, pos_y, x, y);
		cache = m_ChannelsRAMCache->Get(x, y);
		if (cache.size() > 0) {
			LogD(2, "m_ChannelsCache->get(x: %d, y: %d)\n", x, y);
			return cache;
		}
	}
	
	// convert the JSON result into the vector of SpectrumChannel, 
	// push the new informations into the cache and return these values
	m_ProjectionMapper.LocalPosXY2LatLng(pos_x, pos_y, lat, lng);
	LogL(5, "GoogleAPIClient::PostAPI(lat: %lf, lng: %lf)\n", lat, lng);
	
	if (m_ApiClient == nullptr)
		throw MakeException(std::runtime_error, std::string("You have to set a concrete instance of ASpectrumApiClient before calling ") + __func__ + "() function");
	
	cache = m_ApiClient->GetSpectrumChannels(lat, lng);
	
	if (m_UseCache)
		m_ChannelsRAMCache->Push(x, y, cache);
	
	return cache;
}