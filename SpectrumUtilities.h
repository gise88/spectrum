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

#include "definitions.h"


#ifndef SPECTRUMUTILITIES_H
#define SPECTRUMUTILITIES_H

namespace utility {
	
	namespace conversion {
		__PRE_FORCEINLINE__ double deg2rad(double deg) __POST_FORCEINLINE__;
		
		__PRE_FORCEINLINE__ double rad2deg(double deg) __POST_FORCEINLINE__;
	}
	
	namespace earth {
		double distance(double lat1d, double lon1d, double lat2d, double lon2d);
		
		void derived_position(double srclat, double srclon, double *dstlat, double *dstlon, unsigned int meters, double bearing);		
	}
}

#endif /* SPECTRUMUTILITIES_H */

