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


#include <gtest/gtest.h>

#include "SpectrumConstants.h"
#include "ProjectionMapper.h"



TEST(ProjectionMapperTest, test1) {

	ProjectionMapper gs_instance_proj_mapper(42.0986, -75.9183, 200, 150, 50);
	ProjectionMapper& pm = ProjectionMapper::Instance();
	
	uint idx_x, idx_y;
	
	
	pm.LatLng2IndexXY(42.0986, -75.9183, idx_x, idx_y);
	
	EXPECT_EQ(idx_x, 0);
	EXPECT_EQ(idx_y, 0);
	
	pm.LatLng2IndexXY(pm.m_NWLat-0.000001, pm.m_NWLon-0.000001, idx_x, idx_y);
	
	EXPECT_EQ(idx_x, 3);
	EXPECT_EQ(idx_y, 2);
	
	
	
	pm.LocalPosXY2IndexXY(0, 0, idx_x, idx_y);
			
	EXPECT_EQ(idx_x, 0);
	EXPECT_EQ(idx_y, 0);
}

