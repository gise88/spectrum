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

SpectrumChannelsCache::SpectrumChannelsCache(uint cell_width_count, uint cell_height_count)
: m_CellWidthCount(cell_width_count), m_CellHeightCount(cell_height_count) {
	LogD(0, "SpectrumChannelsCache(%d, %d)\n", cell_width_count, cell_height_count);
	
	m_Entries.reserve(m_CellWidthCount);
	for (uint x = 0; x < m_CellWidthCount; x++) {
		std::vector<Entry *> tmp;
		tmp.reserve(m_CellHeightCount);
		for (uint y = 0; y < m_CellHeightCount; y++)
			tmp.push_back(new Entry());
		m_Entries.push_back(tmp);
	}
	
	LogL(5, "Cache grid dimension: %ldx%ld\n", m_CellWidthCount, m_CellHeightCount);
}

SpectrumChannelsCache::~SpectrumChannelsCache() {
	LogD(0, "~SpectrumChannelsCache()\n");
	for (auto x_item : m_Entries)
		for (auto y_item : x_item)
			delete y_item;
}

void SpectrumChannelsCache::push(uint x, uint y, SpectrumChannel *item) {
	LogD(0, "push(%d, %d, {%s})\n", x, y, item->toString());
	if (x >= m_CellWidthCount)
		throw MakeException(std::out_of_range, "x (" + std::to_string(x) + ") out of range: ");
	if (y >= m_CellHeightCount)
		throw MakeException(std::out_of_range, "y (" + std::to_string(y) + ") out of range: ");
	m_Entries[x][y]->push(item);
}

void SpectrumChannelsCache::push(uint x, uint y, std::vector<SpectrumChannel>& vec) {
	LogD(0, "push(%d, %d, list)\n", x, y);
	
	for (SpectrumChannel item : vec)
		this->push(x, y, &item);
}

const std::vector<SpectrumChannel> SpectrumChannelsCache::get(uint x, uint y) {
	LogD(0, "get(%d, %d)\n", x, y);
	
	return m_Entries[x][y]->get();
}

/*
	SpectrumChannelsCache::Entry
 */

SpectrumChannelsCache::Entry::Entry() {
	LogD(0, "Entry()\n");
}

SpectrumChannelsCache::Entry::~Entry() {
	LogD(0, "~Entry()\n");
}

void SpectrumChannelsCache::Entry::push(SpectrumChannel *item) {
	LogD(0, "Entry::push({%s})\n", item->toString());
	m_Channels.push_back(*item);
}

const std::vector<SpectrumChannel> SpectrumChannelsCache::Entry::get() {
	LogD(0, "Entry::get()\n");
	return m_Channels;
}