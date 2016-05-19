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


#include "json.hpp"  // https://github.com/nlohmann/json
using JSON = nlohmann::json;

#include "Log.h"
#include "SpectrumManager.h"
#include "SpectrumConstants.h"
#include "GoogleAPIClient.h"






// global singleton instance of SpectrumManager class
static SpectrumManager gs_instance_spectrum_manager(44.494198, 11.346721, AREA_WIDTH_SIZE, AREA_HEIGHT_SIZE, CELL_SIDE_SIZE);

SpectrumManager::SpectrumManager(double SW_lat, double SW_lon, double area_width, double area_height, double cell_side_size, bool use_cache)
: m_UseCache(use_cache), m_ProjectionMapper(SW_lat, SW_lon, area_width, area_height, cell_side_size),
		m_ChannelsCache(SW_lat, SW_lon, area_width, area_height, cell_side_size) {
	LogD(0, "SpectrumManager(%lf, %lf, %.2lf, %.2lf, %.2lf, %s)\n", SW_lat, SW_lon, area_width, area_height, cell_side_size, use_cache ? "true" : "false");
}

SpectrumManager::~SpectrumManager() {
	LogD(0, "~SpectrumManager()\n");
}

const std::vector<SpectrumChannel> SpectrumManager::GetChannels(uint pos_x, uint pos_y, double antenna_height) {
	LogD(0, "GetChannels(%d, %d, %lf)\n", pos_x, pos_y, antenna_height);
	
	std::vector<SpectrumChannel> cache;
	
	// TODO:  request to the google api
	if (m_UseCache) {
		uint x, y;
		m_ProjectionMapper.LocalPosXY2IndexXY(pos_x, pos_y, x, y);
		cache = m_ChannelsCache.get(x, y);
		if (cache.size() > 0)
			return cache;
	}
	
	try {
		JSON res = GoogleAPIClient::PostAPI(42.0986, -75.9183, antenna_height);
		printf("res: %s\n\n", res.dump(2).c_str());
	} catch (JsonParseException &e) {
		printf("%s\n\n", e.what());
	} catch (CURLErrorException &e) {
		printf("%s\n\n", e.what());
	}
	
	// convert the JSON result into the vector of SpectrumChannel, 
	// push the new informations into the cache and return these values
	
	return cache;
}
