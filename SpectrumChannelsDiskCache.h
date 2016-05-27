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



#ifndef SPECTRUMCHANNELSDISKCACHE_H
#define SPECTRUMCHANNELSDISKCACHE_H

#include <vector>
#include <functional>

#include "SpectrumChannelsRAMCache.h"

class SpectrumChannelsDiskCache {
public:
	SpectrumChannelsDiskCache(std::string configuration);
	virtual ~SpectrumChannelsDiskCache();
	
	void LoadData(std::function<bool(char *, uint &, uint &)> foreach_file_func, 
		std::function<void(uint, uint, std::vector<SpectrumChannel>&)> foreach_location_read);
	
	void WriteData(double lat, double lng, std::vector<SpectrumChannel>& vec);
	
	static void EnsureCacheFolder();
	
private:
	
	std::string m_CacheFolder;
};

#endif /* SPECTRUMCHANNELSDISKCACHE_H */

