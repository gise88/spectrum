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

#include "Utilities.h"
#include "SpectrumChannelsCacheFactory.h"


SpectrumChannelsRAMCache* SpectrumChannelsCacheFactory::CreateSpectrumChannelsRAMCache(
	double SW_lat, double SW_lon, double area_width, double area_height, double cell_side_size) {
	LogD(0, "CreateSpectrumChannelsRAMCache(%lf, %lf, %.2lf, %.2lf, %.2lf)\n", SW_lat, SW_lon, area_width, area_height, cell_side_size);
	
	if (cell_side_size == 0.0)
		DieWithError(1, "cell length side cannot be zero!");
	
	if (fmod(area_width, cell_side_size) != 0.0)
		DieWithError(1, "area_width %% cell_side_length != 0.0");
	uint cell_width_count = (uint) area_width/cell_side_size;
	
	if (fmod(area_height, cell_side_size) != 0.0)
		DieWithError(1, "area_height %% cell_side_length != 0.0");
	uint cell_height_count = (uint) area_height/cell_side_size;
	
	return new SpectrumChannelsRAMCache(cell_width_count, cell_height_count);
}

