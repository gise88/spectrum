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


typedef struct frequency_ranges_s {
	double maxPowerDBm;
	unsigned int startHz;
	unsigned int stopHz;
} frequency_ranges_t;


class FrequencyRangesCache : public Singleton<FrequencyRangesCache> {
public:
	
	class Entry {
	public:
		Entry(size_t x, size_t y);		
		virtual ~Entry();
		
		void push(frequency_ranges_t *item);
		std::list<frequency_ranges_t *> get();
		
		size_t getPosX() { return this->m_PosX; }
		size_t getPosY() { return this->m_PosY; }
		
	private:
		std::list<frequency_ranges_t *> m_Ranges;
		size_t m_PosX;
		size_t m_PosY;
    };
	
	FrequencyRangesCache(double SW_lat, double SW_lon, double NE_lat, double NE_lon, size_t width, size_t height);
	virtual ~FrequencyRangesCache();
	
	void push(int x, int y, frequency_ranges_t *item);
	std::list<frequency_ranges_t *> get(int x, int y);
	
private:
	std::vector< std::vector<Entry *> > m_entries;
};


#endif /* FREQUENCYRANGESCACHE_H */

