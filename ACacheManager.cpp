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

#include "ACacheManager.h"
#include "Utilities.h"

ACacheManager::ACacheManager()
: m_ChannelsRAMCache(nullptr) {
	LogD(0, "ACacheManager()\n");
}

ACacheManager::~ACacheManager() {
	LogD(0, "~ACacheManager()\n");
	delete m_ChannelsRAMCache;
}

void ACacheManager::InitializeCache(uint cell_width_count, uint cell_height_count) {
	LogD(0, "InitializeCache(%d, %d)\n", cell_width_count, cell_height_count);
	
	if (m_ChannelsRAMCache != nullptr)
		throw MakeException(std::runtime_error, std::string("The cache is already initialized.. which is a problem!"));
	m_ChannelsRAMCache = new SpectrumChannelsRAMCache(cell_width_count, cell_height_count);
}

void ACacheManager::LoadCacheFromDisk() {
	LogD(0, "LoadCacheFromDisk()\n");

	std::string current_configuration = GetCurrentConfiguration();	
	LogD(10, "TOOOODOOO: current_configuration = %s\n", current_configuration.c_str());
}

std::vector<SpectrumChannel> ACacheManager::GetFromCache(uint x, uint y) {
	if (m_ChannelsRAMCache == nullptr)
		throw MakeException(std::runtime_error, std::string("You have to initialize the cache before calling ") + __func__ + "() function");
	return m_ChannelsRAMCache->Get(x, y);
}

void ACacheManager::PushIntoCache(uint x, uint y, std::vector<SpectrumChannel>& vec) {
	if (m_ChannelsRAMCache == nullptr)
		throw MakeException(std::runtime_error, std::string("You have to initialize the cache before calling ") + __func__ + "() function");
	m_ChannelsRAMCache->Push(x, y, vec);
}