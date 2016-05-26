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

#include "Log.h"
#include "Utilities.h"
#include "ACacheManager.h"
#include "SpectrumChannelsDiskCache.h"



ACacheManager::ACacheManager()
: m_ChannelsRAMCache(nullptr), m_ChannelsDiskCache(nullptr) {
	LogD(0, "ACacheManager()\n");
}

ACacheManager::~ACacheManager() {
	LogD(0, "~ACacheManager()\n");
	if (m_ChannelsRAMCache != nullptr)
		delete m_ChannelsRAMCache;
	if (m_ChannelsDiskCache != nullptr)
		delete m_ChannelsDiskCache;
}

void ACacheManager::InitializeCache(uint cell_width_count, uint cell_height_count) {
	LogD(0, "InitializeCache(%d, %d)\n", cell_width_count, cell_height_count);
	
	if (m_ChannelsRAMCache != nullptr || m_ChannelsDiskCache != nullptr)
		throw MakeException(std::runtime_error, std::string("The cache is already initialized.. which is a problem!"));
	
	m_ChannelsRAMCache = new SpectrumChannelsRAMCache(cell_width_count, cell_height_count);	
	m_ChannelsDiskCache = new SpectrumChannelsDiskCache(GetCurrentConfiguration());
	LogD(10, "TOOOODOOO: current_configuration\n");
}

void ACacheManager::LoadCacheFromDisk() {
	LogD(0, "LoadCacheFromDisk()\n");

	ProjectionMapper *projectionMapper = ProjectionMapper::InstancePtr();
	auto alias_ChannelsRAMCache = m_ChannelsRAMCache;
	
	m_ChannelsDiskCache->LoadData(
		[projectionMapper](char *filename, uint &idx_x, uint &idx_y) mutable -> bool {
			LogD(0, "[Lambda]: (char *filename, uint &idx_x, uint &idx_y)(%s, *idx_x*, *idx_y*)\n", filename);
			double lat, lng;
			if (sscanf(filename, "%lf,%lf.csv", &lat, &lng) == 2) {
				try {
					projectionMapper->LatLng2IndexXY(lat, lng, idx_x, idx_y);
				} catch(std::out_of_range& e) {
					return false;
				}
				LogD(0, "%lf  %lf  ->  idx_(x, y)=(%d, %d)\n", lat, lng, idx_x, idx_y);
				return true;
			}
			return false;
		},[alias_ChannelsRAMCache](std::vector<SpectrumChannel>& vec, uint x, uint y) -> void {
			LogD(0, "[Lambda]: (std::vector<SpectrumChannel>& vec, uint x, uint y)(*vec*, %d, %d)\n", x, y);
			alias_ChannelsRAMCache->Push(x, y, vec);
		});
}

std::vector<SpectrumChannel> ACacheManager::GetFromCache(uint x, uint y) {
	LogD(0, "GetFromCache(%d, %d)\n", x, y);
	if (m_ChannelsRAMCache == nullptr)
		throw MakeException(std::runtime_error, std::string("You have to initialize the cache before calling ") + __func__ + "() function");
	return m_ChannelsRAMCache->Get(x, y);
}

void ACacheManager::PushIntoCache(uint x, uint y, std::vector<SpectrumChannel>& vec) {
	LogD(0, "PushIntoCache(%d, %d, *vec*)\n", x, y);
	if (m_ChannelsRAMCache == nullptr)
		throw MakeException(std::runtime_error, std::string("You have to initialize the cache before calling ") + __func__ + "() function");
	m_ChannelsRAMCache->Push(x, y, vec);
}