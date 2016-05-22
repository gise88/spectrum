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



#ifndef SPECTRUMCHANNELSCACHEFACTORY_H
#define SPECTRUMCHANNELSCACHEFACTORY_H

#include "SpectrumChannelsRAMCache.h"
#include "IConfiguration.h"


class SpectrumChannelsCacheFactory {
public:
	
	static SpectrumChannelsRAMCache* CreateSpectrumChannelsRAMCache(double SW_lat, double SW_lon, double area_width, double area_height, double cell_side_size);
};

#endif /* SPECTRUMCHANNELSCACHEFACTORY_H */

