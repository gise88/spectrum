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

#include <random>
#include <cstdlib>

#include "Log.h"
#include "Exceptions.h"
#include "SpectrumManager.h"
#include "GoogleAPIClient.h"
#include "SpectrumConstants.h"


// global singleton instance of SpectrumManager class



/*
 * 
 */
int main(int argc, char** argv) {

	SpectrumManager gs_instance_spectrum_manager(42.0986, -75.9183, AREA_WIDTH_SIZE, AREA_HEIGHT_SIZE, CELL_SIDE_SIZE);

	
	SpectrumManager &spectrumManager = SpectrumManager::Instance();
	std::unique_ptr<GoogleAPIClient> apiclient(new GoogleAPIClient(2.0, DeviceType::MODE_1));

	try {		
		spectrumManager.AddSpectrumApiClient("MODE1_2.0", std::move(apiclient));		
		// It will crash because the instance "apiclient" was moved inside the spectrumManager
		// printf("%s", apiclient->GetCurrentConfiguration().c_str());

#if 0
		uint num=0;
		for (int x=0; x<AREA_WIDTH_SIZE; x+=CELL_SIDE_SIZE) {
			for (int y=0; y<AREA_HEIGHT_SIZE; y+=CELL_SIDE_SIZE) {
				num++;
				spectrumManager.GetChannels("MODE1_2.0", x, y);
				printf("num: %d\n", num);
			}
		}
#endif
		
#if 1
		uint tests = 10000;
		std::random_device rd;     // only used once to initialise (seed) engine
		std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
		std::uniform_int_distribution<uint> uniWidth(0, AREA_WIDTH_SIZE - 1); // guaranteed unbiased
		std::uniform_int_distribution<uint> uniHeight(0, AREA_HEIGHT_SIZE -1); // guaranteed unbiased
		for (int i=0; i<tests; i++) {
			spectrumManager.GetChannels("MODE1_2.0", uniWidth(rng), uniHeight(rng));
		}
#endif
		
		
#if 0	
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
#endif
		
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