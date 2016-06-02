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

/* 
 * File:   SpectrumConstants.h
 * Author: Gianluca Iselli <gianluca.iselli@gmail.com>
 *
 * Created on May 11, 2016, 5:49 PM
 */

#ifndef SPECTRUMCONSTANTS_H
#define SPECTRUMCONSTANTS_H


#define GOOGLE_SPECTRUM_API_KEY_FILE	"GoogleSpectrumApiKey.txt"
#define GOOGLE_SPECTRUM_API_URL			"https://www.googleapis.com/rpc"

#define DEVICE_TYPE_FIXED				"FIXED"
#define DEVICE_TYPE_MODE_1				"MODE_1"
#define DEVICE_TYPE_MODE_2				"MODE_2"
#define FIRST_CHANNEL_AVAILABLE			21
#define FIRST_CHANNEL_AVAILABLE_HZ		512000000

#define DEFAULT_ANTENNA_HEIGHT		2.0
#define DEFAULT_DEVICE_TYPE			DEVICE_TYPE_MODE_1


#define AREA_WIDTH_SIZE		2000 //meters
#define AREA_HEIGHT_SIZE	1500 //meters
#define CELL_SIDE_SIZE		50 //meters


//#define DEBUG_CACHE
#ifdef DEBUG_CACHE
#define CACHE_FILES_FOLDER	"/workspace/spectrum-test-cache/"
#else
#define CACHE_FILES_FOLDER	"cache/"
#endif


#endif /* SPECTRUMCONSTANTS_H */

