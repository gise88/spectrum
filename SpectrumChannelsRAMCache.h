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

#ifndef SPECTRUMCHANNELSRAMCACHE_H
#define SPECTRUMCHANNELSRAMCACHE_H

#include <list>
#include <vector>

#include "IConfiguration.h"


struct SpectrumChannel {
	uint number;
	double maxPowerDBm;
	
#ifdef DEBUG
	char __toStringBuffer[100];
	const char* toString() {
		snprintf(__toStringBuffer, 100, "#%d  DBm:%lf", number, maxPowerDBm);
		return __toStringBuffer;
	}
#endif
	
	SpectrumChannel(uint number, double powerDBm)
    :  number(number), maxPowerDBm(powerDBm) {}
	
	SpectrumChannel(SpectrumChannel *item)
	: number(item->number), maxPowerDBm(item->maxPowerDBm) {}
};


class SpectrumChannelsRAMCache {
public:
	
	SpectrumChannelsRAMCache(uint cell_width_count, uint cell_height_count);
	virtual ~SpectrumChannelsRAMCache();
	
	void ClearCache();
	
	void Push(uint x, uint y, std::vector<SpectrumChannel>& vec);
	const std::vector<SpectrumChannel> Get(uint x, uint y);
	
private:
	
	class Entry {
	public:
		Entry();
		virtual ~Entry();
		
		void Clear();
		long unsigned int Size();
		void Push(SpectrumChannel *item);
		const std::vector<SpectrumChannel> Get();
		
	private:
		std::vector<SpectrumChannel> m_Channels;
    };
	
	
	std::vector< std::vector<Entry *> > m_GridEntries;
	
	uint m_CellWidthCount;
	uint m_CellHeightCount;
};


#endif /* SPECTRUMCHANNELSRAMCACHE_H */

