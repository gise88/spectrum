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
#include <cmath> 
#include <stdio.h>

#include "SpectrumUtilities.h"

namespace utility {

	namespace conversion {
		// This function converts decimal degrees to radians
		__PRE_FORCEINLINE__ double deg2rad(double deg) {
			return (deg * M_PI / 180);
		}

		//  This function converts radians to decimal degrees
		__PRE_FORCEINLINE__ double rad2deg(double rad) {
			return (rad * 180 / M_PI);
		}
	}
	
	namespace earth {
		
		
		#define EARTH_RADIUS_KM 6371.0
		
		// thanks to: http://stackoverflow.com/a/10205532
		// better? http://gis.stackexchange.com/questions/144084/using-gdal-c-to-calculate-distance-in-meters
		/**
		 * Returns the distance between two points on the Earth.
		 * Direct translation from http://en.wikipedia.org/wiki/Haversine_formula
		 * @param lat1d Latitude of the first point in degrees
		 * @param lon1d Longitude of the first point in degrees
		 * @param lat2d Latitude of the second point in degrees
		 * @param lon2d Longitude of the second point in degrees
		 * @return The distance between the two points in kilometers
		 */
		double distance(double lat1d, double lon1d, double lat2d, double lon2d) {
			double lat1r, lon1r, lat2r, lon2r, u, v, distance;
			lat1r = conversion::deg2rad(lat1d);
			lon1r = conversion::deg2rad(lon1d);
			lat2r = conversion::deg2rad(lat2d);
			lon2r = conversion::deg2rad(lon2d);
			u = sin((lat2r - lat1r) / 2);
			v = sin((lon2r - lon1r) / 2);
			distance = 2.0 * EARTH_RADIUS_KM * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
			return distance * 1000.0; // in meters
		}
		
		
		/**
		 * Calculates the end-point from a given source at a given range (meters) and bearing (degrees).
		 * This methods uses simple geometry equations to calculate the end-point.
		 * @param srclat Latitude of origin in degrees
		 * @param srclon Longitude of origin in degrees 
		 * @param dstlat Latitude of destination in degrees
		 * @param dstlon Longitude of destination in degrees
		 * @param meters Distance of range in meters
		 * @param bearing Bearing in degrees
		 */
		void derived_position(double srclat, double srclon, double *dstlat, double *dstlon, unsigned int meters, double bearing) {
			double src_lat_rad = conversion::deg2rad(srclat);
			double src_lon_rad = conversion::deg2rad(srclon);
			
			double angular_distance = meters / (EARTH_RADIUS_KM * 1000);
			double course = conversion::deg2rad(bearing);
			
			*dstlat = asin(
				sin(src_lat_rad) * cos(angular_distance) +
				cos(src_lat_rad) * sin(angular_distance) * cos(course));
			*dstlat = conversion::rad2deg(*dstlat);
			
			double dlon = atan2(
				sin(course) * sin(angular_distance) * cos(src_lat_rad),
				cos(angular_distance) - sin(src_lat_rad) * sin(*dstlat));
			*dstlon = (fmod((src_lon_rad + dlon + M_PI), (M_PI * 2))) - M_PI;
			*dstlon = conversion::rad2deg(*dstlon);
		}
	}
}