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

#include <math.h>

#include "Log.h"
#include "Utilities.h"
#include "Exceptions.h"
#include "SpectrumManager.h"
#include "SpectrumConstants.h"
#include "SpectrumChannelsDiskCache.h"


SpectrumManager::SpectrumManager(double SW_lat, double SW_lon, double area_width, double area_height, double cell_side_size, bool use_cache)
: m_UseCache(use_cache), m_ProjectionMapper(SW_lat, SW_lon, area_width, area_height, cell_side_size) {
	LogD(0, "SpectrumManager(%lf, %lf, %.2lf, %.2lf, %.2lf, %s)\n", SW_lat, SW_lon, area_width, area_height, cell_side_size, use_cache ? "true" : "false");

	if (cell_side_size == 0.0)
		DieWithError(1, "cell length side cannot be zero!");
	
	if (fmod(area_width, cell_side_size) != 0.0)
		DieWithError(1, "area_width %% cell_side_length != 0.0");
	m_CellWidthCount = (uint) area_width/cell_side_size;
	
	if (fmod(area_height, cell_side_size) != 0.0)
		DieWithError(1, "area_height %% cell_side_length != 0.0");
	m_CellHeightCount = (uint) area_height/cell_side_size;
	
	if (m_UseCache)
		SpectrumChannelsDiskCache::EnsureCacheFolder();
}

SpectrumManager::~SpectrumManager() {
	LogD(0, "~SpectrumManager()\n");
	m_ApiClientsMap.clear();
}

void SpectrumManager::AddSpectrumApiClient(std::string tag, std::unique_ptr<ASpectrumApiClient>&& api_client) {
	LogD(0, "AddSpectrumApiClient(%s, *api_client*)\n", tag.c_str());
	
	if (api_client == nullptr)
		throw MakeException(std::runtime_error, std::string("You have to set a concrete instance of ASpectrumApiClient before calling ") + __func__ + "() function");
	
	if (m_ApiClientsMap.find(tag) != m_ApiClientsMap.end())
		throw MakeException(std::invalid_argument, "The key \"" + tag + "\" already exists in the map of Api Clients.");
	
	m_ApiClientsMap[tag] = std::move(api_client);
	
	if (m_UseCache) {
		m_ApiClientsMap[tag]->InitializeCache(m_CellWidthCount, m_CellHeightCount);
		m_ApiClientsMap[tag]->LoadCacheFromDisk();
	}
}

const std::vector<SpectrumChannel> SpectrumManager::GetChannels(std::string tag, uint pos_x, uint pos_y) {
	LogD(0, "GetChannels(%d, %d)\n", pos_x, pos_y);
	
	uint x, y;
	double lat, lng;
	ASpectrumApiClient *api_client;
	std::vector<SpectrumChannel> channels;
	
	auto pair = m_ApiClientsMap.find(tag);
	if (pair == m_ApiClientsMap.end())
		throw MakeException(std::invalid_argument, "The key \"" + tag + "\" does not exist in the map of Api Clients.");
	
	api_client = pair->second.get();
	
	if (m_UseCache) {
		m_ProjectionMapper.LocalPosXY2IndexXY(pos_x, pos_y, x, y);
		channels = api_client->GetFromCache(x, y);
		if (channels.size() > 0) {
			LogD(2, "m_ChannelsCache->get(x: %d, y: %d)\n", x, y);
			return channels;
		}
	}
	
	// convert the JSON result into the vector of SpectrumChannel, 
	// push the new informations into the cache and return these values
	m_ProjectionMapper.LocalPosXY2LatLng(pos_x, pos_y, lat, lng);
	LogL(5, "GoogleAPIClient::PostAPI(lat: %lf, lng: %lf)\n", lat, lng);
	
	channels = api_client->GetSpectrumChannels(lat, lng);
	
	if (m_UseCache)
		api_client->PushIntoCache(x, y, channels);
	
	return channels;
}


	
	