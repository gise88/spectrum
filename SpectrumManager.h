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
#include <memory>
#include <unordered_map>

#include "Singleton.h"
#include "ProjectionMapper.h"
#include "ASpectrumApiClient.h"




class SpectrumManager : public Singleton<SpectrumManager> {
public:
	SpectrumManager(double SW_lat, double SW_lon, double area_width, double area_height, double cell_side_size, bool use_cache=true);
	virtual ~SpectrumManager();
	
	void AddSpectrumApiClient(std::string tag, std::unique_ptr<ASpectrumApiClient>&& api_client);
	const std::vector<SpectrumChannel> GetChannels(std::string tag, uint pos_x, uint pos_y);
	
private:
	
	bool m_UseCache;
	uint m_CellWidthCount;
	uint m_CellHeightCount;
	ProjectionMapper m_ProjectionMapper;
	
	std::unordered_map<std::string, std::unique_ptr<ASpectrumApiClient> > m_ApiClientsMap;
	
};

#endif /* SPECTRUMMANAGER_H */

