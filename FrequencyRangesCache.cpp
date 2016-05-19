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

#include <string.h>
#include "SpectrumConstants.h"
#include "SpectrumUtilities.h"
#include "FrequencyRangesCache.h"




// global singleton instance of FrequencyRangesCache class
//static FrequencyRangesCache gs_instance_frequency_ranges_cache(42.990967, -71.463767, 43.272275, -71.042922, AREA_WIDTH_SIZE, AREA_HEIGHT_SIZE);
//static FrequencyRangesCache gs_instance_frequency_ranges_cache(50.666932, 67.019369, 57.894857, 86.202316, AREA_WIDTH_SIZE, AREA_HEIGHT_SIZE);
//static FrequencyRangesCache gs_instance_frequency_ranges_cache(-31.294475, 123.923107, -18.996646, 141.852794, AREA_WIDTH_SIZE, AREA_HEIGHT_SIZE);
static FrequencyRangesCache gs_instance_frequency_ranges_cache(-5.287480, 14.745823, 4.750885, 25.240604, AREA_WIDTH_SIZE, AREA_HEIGHT_SIZE);

/*
	FrequencyRangesCache
 */

FrequencyRangesCache::FrequencyRangesCache(double SW_lat, double SW_lon, double NE_lat, double NE_lon, size_t width, size_t height) {
	std::cout << "FrequencyRangesCache() " << std::endl;
	fflush(stdout);

	if (SW_lat + NE_lat >= 0) {
		double lat_dist = utility::earth::distance(SW_lat, SW_lon, NE_lat, SW_lon);
		double lon_dist = utility::earth::distance(SW_lat, SW_lon, SW_lat, NE_lon);

		double lat_dist2 = utility::earth::distance(SW_lat, NE_lon, NE_lat, NE_lon);
		double lon_dist2 = utility::earth::distance(NE_lat, SW_lon, NE_lat, NE_lon);
		printf("lat dists:  %lf   %lf\n", lat_dist, lat_dist2);
		printf("lon dists:  %lf   NO-%lf\n", lon_dist, lon_dist2);
	} else { // if (SW_lat - NE_lat < 0)
		double lat_dist = utility::earth::distance(SW_lat, SW_lon, NE_lat, SW_lon);
		double lon_dist = utility::earth::distance(SW_lat, SW_lon, SW_lat, NE_lon);

		double lat_dist2 = utility::earth::distance(SW_lat, NE_lon, NE_lat, NE_lon);
		double lon_dist2 = utility::earth::distance(NE_lat, SW_lon, NE_lat, NE_lon);
		printf("lat dists:  %lf   %lf\n", lat_dist, lat_dist2);
		printf("lon dists:  NO-%lf   %lf\n", lon_dist, lon_dist2);
	}

	m_entries.reserve(width);
	for (size_t x = 0; x < width; x++) {
		std::vector<Entry *> tmp;
		m_entries.reserve(width);
		for (size_t y = 0; y < height; y++)
			tmp.push_back(new Entry(x, y));

		m_entries.push_back(tmp);
	}
}

FrequencyRangesCache::~FrequencyRangesCache() {
	std::cout << "~FrequencyRangesCache() " << std::endl;
	fflush(stdout);
	for (auto x_item : m_entries)
		for (auto y_item : x_item)
			delete y_item;
}

void FrequencyRangesCache::push(int x, int y, frequency_ranges_t *item) {
	m_entries[x][y]->push(item);
}

std::list<frequency_ranges_t *> FrequencyRangesCache::get(int x, int y) {
	return m_entries[x][y]->get();
}

/*
	FrequencyRangesCache::Entry
 */

FrequencyRangesCache::Entry::Entry(size_t x, size_t y)
: m_PosX(x), m_PosY(y) {
	//std::cout << "Entry()" << std::endl; fflush(stdout);
}

FrequencyRangesCache::Entry::~Entry() {
	//std::cout << "~Entry()" << std::endl; fflush(stdout);
	for (auto item : m_Ranges)
		free(item);
}

void FrequencyRangesCache::Entry::push(frequency_ranges_t *item) {
	frequency_ranges_t *ptr = (frequency_ranges_t *) malloc(sizeof (frequency_ranges_t));
	memcpy(ptr, item, sizeof (frequency_ranges_t));
	m_Ranges.push_back(ptr);
}

std::list<frequency_ranges_t *> FrequencyRangesCache::Entry::get() {
	return m_Ranges;
}