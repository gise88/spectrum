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



#ifndef ACACHEMANAGER_H
#define ACACHEMANAGER_H

#include <vector>

#include "Log.h"
#include "IConfiguration.h"
#include "SpectrumChannelsRAMCache.h"


class ACacheManager : public IConfiguration {
public:
	ACacheManager();
	virtual ~ACacheManager();

	
	void InitializeCache(uint cell_width_count, uint cell_height_count);
	void LoadCacheFromDisk();
	
	std::vector<SpectrumChannel> GetFromCache(uint x, uint y);
	void PushIntoCache(uint x, uint y, std::vector<SpectrumChannel>& vec);
	
private:
	SpectrumChannelsRAMCache *m_ChannelsRAMCache;
};

#endif /* ACACHEMANAGER_H */

