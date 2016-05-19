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

#include "ProjectionMapper.h"
#include "Utilities.h"

ProjectionMapper::ProjectionMapper(double SW_lat, double SW_lon, double width_area, double height_area, double cell_side_size)
: m_SWLat(SW_lat), m_SWLon(SW_lon), m_AreaWidth(width_area), m_AreaHeight(height_area) {
	LogD(0, "ProjectionMapper(%ld, %ld, %ld, %ld, %ld)\n",  SW_lat, SW_lon, width_area, height_area, cell_side_size);
	int err;

	if (!(m_PJMerc = pj_init_plus("+proj=merc +lat_ts=0 +lon_0=0")))
		DieWithError(1, "Failed to initiate merc proj\n");
	if (!(m_PJLatlng = pj_init_plus("+proj=latlong +ellps=clrk66")))
		DieWithError(1, "Failed to initiate latlong proj\n");

	// Translate the Origin coordinates into Northings and Eastings 
	m_OriginNorthing = SW_lat * DEG_TO_RAD;
	m_OriginEastings = SW_lon * DEG_TO_RAD;

	if ((err = pj_transform(m_PJLatlng, m_PJMerc, 1, 1, &m_OriginEastings, &m_OriginNorthing, NULL)) != 0)
		DieWithError(1, "Failed to transform (SW_lat, SW_lon) - Error code: %d   Error message: %s\n", err, pj_strerrno(err));

	// Add the area size to the Northing/Easting coordinate and transform
	double x = width_area + m_OriginEastings;
	double y = height_area + m_OriginNorthing;
	
	if ((err = pj_transform(m_PJMerc, m_PJLatlng, 1, 1, &x, &y, NULL)) != 0)
		DieWithError(1, "Failed to transform (x,y) - Error code: %d   Error message: %s\n", err, pj_strerrno(err));

	m_NWLat = y * RAD_TO_DEG;
	m_NWLon = x * RAD_TO_DEG;
	
	LogL(0, "m_NWLat: %lf, m_NWLon: %lf\n", m_NWLat, m_NWLon);
}

ProjectionMapper::~ProjectionMapper() {
	LogD(0, "~ProjectionMapper()\n");
	pj_free(m_PJMerc);
	pj_free(m_PJLatlng);
}

