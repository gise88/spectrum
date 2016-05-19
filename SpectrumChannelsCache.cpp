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
#include <string.h>
#include "Utilities.h"
#include "SpectrumChannelsCache.h"




/*
	FrequencyRangesCache
 */

SpectrumChannelsCache::SpectrumChannelsCache(double SW_lat, double SW_lon, double area_width, double area_height, double cell_side_size) {
	LogD(0, "FrequencyRangesCache(%lf, %lf, %.2lf, %.2lf, %.2lf)\n", SW_lat, SW_lon, area_width, area_height, cell_side_size);
	
	if (cell_side_size == 0.0)
		DieWithError(1, "cell length side cannot be zero!");
	
	if (fmod(area_width, cell_side_size) != 0.0)
		DieWithError(1, "area_width %% cell_side_length != 0.0");
	m_CellWidthCount = (uint) area_width/cell_side_size;
	
	if (fmod(area_height, cell_side_size) != 0.0)
		DieWithError(1, "area_height %% cell_side_length != 0.0");
	m_CellHeightCount = (uint) area_height/cell_side_size;
	
	LogL(1, "Cache grid dimension: %ldx%ld\n", m_CellWidthCount, m_CellHeightCount);
	
	m_Entries.reserve(m_CellWidthCount);
	for (uint x = 0; x < m_CellWidthCount; x++) {
		std::vector<Entry *> tmp;
		m_Entries.reserve(m_CellWidthCount);
		for (uint y = 0; y < m_CellHeightCount; y++)
			tmp.push_back(new Entry());
		m_Entries.push_back(tmp);
	}
}

SpectrumChannelsCache::~SpectrumChannelsCache() {
	LogD(0, "~FrequencyRangesCache()\n");
	for (auto x_item : m_Entries)
		for (auto y_item : x_item)
			delete y_item;
}

void SpectrumChannelsCache::push(uint x, uint y, SpectrumChannel *item) {
	LogD(0, "FrequencyRangesCache::push(%d, %d, {%s})\n", x, y, item->toString());
	if (x >= m_CellWidthCount)
		throw MakeException(std::out_of_range, "x (" + std::to_string(x) + ") out of range: ");
	if (y >= m_CellHeightCount)
		throw MakeException(std::out_of_range, "y (" + std::to_string(y) + ") out of range: ");
	m_Entries[x][y]->push(item);
}

void SpectrumChannelsCache::push(uint x, uint y, std::list<SpectrumChannel *> list) {
	LogD(0, "FrequencyRangesCache::push(%d, %d, list)\n", x, y);
	for (SpectrumChannel *item : list)
		this->push(x, y, item);
}

const std::vector<SpectrumChannel> SpectrumChannelsCache::get(uint x, uint y) {
	LogD(0, "FrequencyRangesCache::get(%d, %d)\n", x, y);
	return m_Entries[x][y]->get();
}

/*
	FrequencyRangesCache::Entry
 */

SpectrumChannelsCache::Entry::Entry() {
	LogD(0, "Entry()\n");
}

SpectrumChannelsCache::Entry::~Entry() {
	LogD(0, "~Entry()\n");
}

void SpectrumChannelsCache::Entry::push(SpectrumChannel *item) {
	LogD(0, "FrequencyRangesCache::Entry::push({%s})\n", item->toString());
	m_Channels.push_back(*item);
}

const std::vector<SpectrumChannel> SpectrumChannelsCache::Entry::get() {
	LogD(0, "FrequencyRangesCache::Entry::get()\n");
	return m_Channels;
}