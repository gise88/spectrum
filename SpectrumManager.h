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



#ifndef SPECTRUMMANAGER_H
#define SPECTRUMMANAGER_H

#include <list>
#include <vector>

#include "json.hpp"  // https://github.com/nlohmann/json
using JSON = nlohmann::json;

#include "Singleton.h"
#include "SpectrumChannelsCache.h"
#include "ProjectionMapper.h"




class SpectrumManager : public Singleton<SpectrumManager> {
public:
	SpectrumManager(double SW_lat, double SW_lon, double area_width, double area_height, double cell_side_size, bool use_cache=true);
	virtual ~SpectrumManager();
	
	const std::vector<SpectrumChannel> GetChannels(uint pos_x, uint pos_y, double antenna_height = 30.0);
	
private:
	
	std::vector<SpectrumChannel> JSONSpectrum2SpectrumChannels(JSON& res);
	
	
	bool m_UseCache;
	ProjectionMapper m_ProjectionMapper;
	SpectrumChannelsCache *m_ChannelsCache;
	
};

#endif /* SPECTRUMMANAGER_H */

