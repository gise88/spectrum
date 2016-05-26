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

ProjectionMapper::ProjectionMapper(double SW_lat, double SW_lon, double area_width, double area_height, double cell_side_size)
: m_SWLat(SW_lat), m_SWLon(SW_lon), m_AreaWidth(area_width), m_AreaHeight(area_height), m_CellSideSize(cell_side_size) {
	LogD(0, "ProjectionMapper(%lf, %lf, %.2lf, %.2lf, %.2lf)\n",  SW_lat, SW_lon, area_width, area_height, cell_side_size);
	int err;

	if (!(m_PJMerc = pj_init_plus("+proj=merc +lat_ts=0 +lon_0=0")))
		DieWithError(1, "Failed to initiate merc proj\n");
	if (!(m_PJLatlng = pj_init_plus("+proj=latlong +ellps=clrk66")))
		DieWithError(1, "Failed to initiate latlong proj\n");

	// Translate the Origin coordinates into Northings and Eastings 
	m_OriginNorthing = m_SWLat * DEG_TO_RAD;
	m_OriginEastings = m_SWLon * DEG_TO_RAD;

	if ((err = pj_transform(m_PJLatlng, m_PJMerc, 1, 1, &m_OriginEastings, &m_OriginNorthing, NULL)) != 0)
		DieWithError(1, "Failed to transform (SW_lat, SW_lon) - Error code: %d   Error message: %s\n", err, pj_strerrno(err));

	// Add the area size to the Northing/Easting coordinate and transform
	double x = area_width + m_OriginEastings;
	double y = area_height + m_OriginNorthing;
	
	if ((err = pj_transform(m_PJMerc, m_PJLatlng, 1, 1, &x, &y, NULL)) != 0)
		DieWithError(1, "Failed to transform (x,y) - Error code: %d   Error message: %s\n", err, pj_strerrno(err));

	m_NWLat = y * RAD_TO_DEG;
	m_NWLon = x * RAD_TO_DEG;
	
	LogD(1, "NWLat: %lf, NWLon: %lf\n", m_NWLat, m_NWLon);
}

ProjectionMapper::~ProjectionMapper() {
	LogD(0, "~ProjectionMapper()\n");
	pj_free(m_PJMerc);
	pj_free(m_PJLatlng);
}


void ProjectionMapper::LocalPosXY2IndexXY(uint pos_x, uint pos_y, uint& idx_x, uint& idx_y) {
	LogD(0, "LocalPosXY2IndexXY(%d, %d, *idx_x*, *idx_y*)\n", pos_x, pos_y);
	
	if (pos_x >= m_AreaWidth)
		throw MakeException(std::out_of_range, "pos_x("+std::to_string(pos_x)+") >= m_AreaWidth");
	if (pos_y >= m_AreaHeight)
		throw MakeException(std::out_of_range, "pos_y("+std::to_string(pos_y)+") >= m_AreaHeight");
	
	idx_x = (uint)floor((double)pos_x / m_CellSideSize);
	idx_y = (uint)floor((double)pos_y / m_CellSideSize);
	
	LogD(1, "LocalPosXY2IndexXY (%d, %d) -> idx_x: %d  idx_y: %d\n", pos_x, pos_y, idx_x, idx_y);
}

void ProjectionMapper::LocalPosXY2LatLng(uint pos_x, uint pos_y, double& lat, double& lng) {
	LogD(0, "LocalPosXPosY2LatLng(%d, %d, *lat*, *lng*)\n", pos_x, pos_y);
	
	int err;
	
	if (pos_x >= m_AreaWidth)
		throw MakeException(std::out_of_range, "pos_x("+std::to_string(pos_x)+") >= m_AreaWidth");
	if (pos_y >= m_AreaHeight)
		throw MakeException(std::out_of_range, "pos_y("+std::to_string(pos_y)+") >= m_AreaHeight");
	
	double x = pos_x + m_OriginEastings;
    double y = pos_y + m_OriginNorthing;
		
	if ((err = pj_transform(m_PJMerc, m_PJLatlng, 1, 1, &x, &y, NULL)) != 0)
		DieWithError(1, "Failed to transform (x,y) - Error code: %d   Error message: %s\n", err, pj_strerrno(err));
	
	lat = y * RAD_TO_DEG;
	lng = x * RAD_TO_DEG;
	
	LogD(1, "LocalPosXY2LatLng (%d, %d) -> lat: %lf  lng: %lf\n", pos_x, pos_y, lat, lng);
}

void ProjectionMapper::LatLng2IndexXY(double lat, double lng, uint& idx_x, uint& idx_y) {
	LogD(0, "LatLng2IndexXY(%lf, %lf, *idx_x*, *idx_y*)\n", lat, lng);
	
	int err;
	double pos_x, pos_y;
	
	double east = lng * DEG_TO_RAD;
	double north = lat * DEG_TO_RAD;
	
	if ((err = pj_transform(m_PJLatlng, m_PJMerc, 1, 1, &east, &north, NULL)) != 0)
		DieWithError(1, "Failed to transform (SW_lat, SW_lon) - Error code: %d   Error message: %s\n", err, pj_strerrno(err));
	
	pos_x = north - m_OriginNorthing;
	pos_y = east - m_OriginEastings;
	
	if (pos_x >= m_AreaWidth)
		throw MakeException(std::out_of_range, "pos_x("+std::to_string(pos_x)+") >= m_AreaWidth");
	if (pos_x < 0)
		throw MakeException(std::out_of_range, "pos_x("+std::to_string(pos_x)+") < 0");
	if (pos_y >= m_AreaHeight)
		throw MakeException(std::out_of_range, "pos_y("+std::to_string(pos_y)+") > m_AreaHeight");
	if (pos_y < 0)
		throw MakeException(std::out_of_range, "pos_y("+std::to_string(pos_y)+") < 0");
	
	LogD(1, "LatLng2IndexXY (%lf, %lf) -> idx_x: %d  idx_y: %d\n", lat, lng, idx_x, idx_y);
}