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



#ifndef FREQUENCYRANGESCACHE_H
#define FREQUENCYRANGESCACHE_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <list>
#include <vector>

#include "Singleton.h"
#include "ProjectionMapper.h"


struct FrequencyRange {
	double maxPowerDBm;
	unsigned int startHz;
	unsigned int stopHz;
	
#ifdef DEBUG
	char __toStringBuffer[100];
	const char* toString() {
		snprintf(__toStringBuffer, 100, "DBm:%lf, startHZ:%d, stopHz:%d", maxPowerDBm, startHz, stopHz);
		return __toStringBuffer;
	}
#endif
	
	FrequencyRange(double powerDBm, unsigned int startHz, unsigned int stopHz)
    : maxPowerDBm(powerDBm), startHz(startHz), stopHz(stopHz) {}
	
	FrequencyRange(FrequencyRange *item)
	: maxPowerDBm(item->maxPowerDBm), startHz(item->startHz), stopHz(item->stopHz) {}
};


class FrequencyRangesCache : public Singleton<FrequencyRangesCache> {
public:
	
	class Entry {
	public:
		Entry();
		virtual ~Entry();
		
		void push(FrequencyRange *item);
		const std::list<FrequencyRange> get();
		
	private:
		std::list<FrequencyRange> m_Ranges;
    };
	
	FrequencyRangesCache(double SW_lat, double SW_lon, double area_width, double area_height, double cell_side_size);
	virtual ~FrequencyRangesCache();
	
	void push(uint x, uint y, FrequencyRange *item);
	void push(uint x, uint y, std::list<FrequencyRange *> list);
	const std::list<FrequencyRange> get(uint x, uint y);
	
private:
	
	ProjectionMapper m_ProjectionMapper;
	std::vector< std::vector<Entry *> > m_Entries;
	
	uint m_CellWidthCount;
	uint m_CellHeightCount;
};


#endif /* FREQUENCYRANGESCACHE_H */

