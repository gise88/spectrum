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

#ifndef PROJECTIONMAPPER_H
#define PROJECTIONMAPPER_H

#include <proj_api.h>

#include "Singleton.h"


class ProjectionMapper : public Singleton<ProjectionMapper> {
public:
	
	ProjectionMapper(double SW_lat, double SW_lon, double area_width, double area_height, double cell_side_size);
	virtual ~ProjectionMapper();
	
	void LocalPosXY2IndexXY(uint pos_x, uint pos_y, uint& idx_x, uint& idx_y);
	void LocalPosXY2LatLng(uint pos_x, uint pos_y, double& lat, double& lng);
	void LatLng2IndexXY(double lat, double lng, uint& idx_x, uint& idx_y);
	
	
private:

	double m_SWLat;
	double m_SWLon;
	double m_NWLat;
	double m_NWLon;
	double m_AreaWidth;
	double m_AreaHeight;
	double m_CellSideSize;
	
	projPJ m_PJMerc;
	projPJ m_PJLatlng;
	double m_OriginNorthing;
	double m_OriginEastings;
};

#endif /* PROJECTIONMAPPER_H */

