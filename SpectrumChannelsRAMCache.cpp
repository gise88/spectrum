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
#include "SpectrumChannelsRAMCache.h"




/*
	SpectrumChannelsRAMCache
 */

SpectrumChannelsRAMCache::SpectrumChannelsRAMCache(uint cell_width_count, uint cell_height_count)
: m_CellWidthCount(cell_width_count), m_CellHeightCount(cell_height_count) {
	LogD(0, "SpectrumChannelsRAMCache(%d, %d)\n", cell_width_count, cell_height_count);
	
	m_GridEntries.reserve(m_CellWidthCount);
	for (uint x = 0; x < m_CellWidthCount; x++) {
		std::vector<Entry *> tmp;
		tmp.reserve(m_CellHeightCount);
		for (uint y = 0; y < m_CellHeightCount; y++)
			tmp.push_back(new Entry());
		m_GridEntries.push_back(tmp);
	}
	
	LogL(5, "Cache grid dimension: %ldx%ld\n", m_CellWidthCount, m_CellHeightCount);
}

SpectrumChannelsRAMCache::~SpectrumChannelsRAMCache() {
	LogD(0, "~SpectrumChannelsRAMCache()\n");
	for (std::vector<Entry *> entries : m_GridEntries)
		for (Entry * entry : entries)
			delete entry;
}

void SpectrumChannelsRAMCache::ClearCache() {
	for (std::vector<Entry *> entries : m_GridEntries)
		for (Entry * entry : entries)
			entry->Clear();
}

void SpectrumChannelsRAMCache::Push(uint x, uint y, SpectrumChannel *item) {
	LogD(0, "push(%d, %d, {%s})\n", x, y, item->toString());
	if (x >= m_CellWidthCount)
		throw MakeException(std::out_of_range, "x (" + std::to_string(x) + ") out of range: ");
	if (y >= m_CellHeightCount)
		throw MakeException(std::out_of_range, "y (" + std::to_string(y) + ") out of range: ");
	m_GridEntries[x][y]->Push(item);
}

void SpectrumChannelsRAMCache::Push(uint x, uint y, std::vector<SpectrumChannel>& vec) {
	LogD(0, "push(%d, %d, list)\n", x, y);
	
	for (SpectrumChannel item : vec)
		this->Push(x, y, &item);
}

const std::vector<SpectrumChannel> SpectrumChannelsRAMCache::Get(uint x, uint y) {
	LogD(0, "get(%d, %d)\n", x, y);
	if (x >= m_CellWidthCount)
		throw MakeException(std::out_of_range, "x (" + std::to_string(x) + ") out of range: ");
	if (y >= m_CellHeightCount)
		throw MakeException(std::out_of_range, "y (" + std::to_string(y) + ") out of range: ");
	return m_GridEntries[x][y]->Get();
}

/*
	SpectrumChannelsRAMCache::Entry
 */

SpectrumChannelsRAMCache::Entry::Entry() {
	LogD(0, "Entry()\n");
}

SpectrumChannelsRAMCache::Entry::~Entry() {
	LogD(0, "~Entry()\n");
}

void SpectrumChannelsRAMCache::Entry::Clear() {
	LogD(0, "Entry::Clear()\n");
	m_Channels.clear();
}

void SpectrumChannelsRAMCache::Entry::Push(SpectrumChannel *item) {
	LogD(0, "Entry::push({%s})\n", item->toString());
	m_Channels.push_back(*item);
}

const std::vector<SpectrumChannel> SpectrumChannelsRAMCache::Entry::Get() {
	LogD(0, "Entry::get()\n");
	return m_Channels;
}