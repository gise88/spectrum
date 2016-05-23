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

// https://en.wikipedia.org/wiki/Hungarian_notation


#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <cstdlib>

#include "Log.h"
#include "Exceptions.h"
#include "SpectrumConstants.h"
#include "SpectrumManager.h"

#include "Utilities.h"
#include "GoogleAPIClient.h"

// global singleton instance of SpectrumManager class
static SpectrumManager gs_instance_spectrum_manager(42.0986, -75.9183, AREA_WIDTH_SIZE, AREA_HEIGHT_SIZE, CELL_SIDE_SIZE);
//static SpectrumManager gs_instance_spectrum_manager(40.814194, -73.501308, AREA_WIDTH_SIZE, AREA_HEIGHT_SIZE, CELL_SIDE_SIZE);

/*
 * 
 */
int main(int argc, char** argv) {

	SpectrumManager &spectrumManager = SpectrumManager::Instance();
	std::unique_ptr<GoogleAPIClient> apiclient(new GoogleAPIClient(2.0, DeviceType::MODE_1));
	
	try {		
		spectrumManager.AddSpectrumApiClient("MODE1_2.0", std::move(apiclient));
		
		// It will crash because the instance "apiclient" was moved inside the spectrumManager
		// printf("%s", apiclient->GetCurrentConfiguration().c_str());
		
		// the cache is empty so need to download all the data
		spectrumManager.GetChannels("MODE1_2.0", 0, 0);
		spectrumManager.GetChannels("MODE1_2.0", 50, 0);
		spectrumManager.GetChannels("MODE1_2.0", 0, 50);
		spectrumManager.GetChannels("MODE1_2.0", 0, 100);
		spectrumManager.GetChannels("MODE1_2.0", 100, 0);
		
		// the cache already has the following items
		spectrumManager.GetChannels("MODE1_2.0", 0, 0);
		spectrumManager.GetChannels("MODE1_2.0", 50, 0);
		spectrumManager.GetChannels("MODE1_2.0", 0, 50);
		spectrumManager.GetChannels("MODE1_2.0", 0, 100);
		spectrumManager.GetChannels("MODE1_2.0", 100, 0);
		
	} catch (CURLErrorException &e) {
		printf("%s\n\n", e.what());
	} catch (JsonParseException &e) {
		printf("%s\n\n", e.what());
	} catch (JsonWithErrorException &e) {
		printf("%s\n\n", e.what());
	} catch (std::out_of_range &e) {
		printf("%s\n\n", e.what());
	} catch (std::invalid_argument &e) {
		printf("%s\n\n", e.what());
	} catch (std::runtime_error &e) {
		printf("%s\n\n", e.what());
	}

	return 0;
}