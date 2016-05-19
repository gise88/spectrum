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
#include "json.hpp"  // https://github.com/nlohmann/json

#include "Log.h"
#include "Exceptions.h"

#include "GoogleAPIClient.h"
#include "SpectrumUtilities.h"
#include "FrequencyRangesCache.h"

using namespace std;
using JSON = nlohmann::json;

#include <string>
#include <utility>




#define LogT(lev, ...)	if (lev>LOG_LIMIT)	Log::Instance().m_log(__VA_ARGS__)



/*
 * 
 */
int main(int argc, char** argv) {
	
//	try {
//		JSON res = GoogleAPIClient::PostAPI(42.0986, -75.9183, 30.0);
//		printf("res: %s\n\n", res.dump(2).c_str());
//	} catch (JsonParseException &e) {
//		printf("%s\n\n", e.what());
//	} catch (CURLErrorException &e) {
//		printf("%s\n\n", e.what());
//	}
	
	frequency_ranges_t range1;
	range1.maxPowerDBm = 15.2342342;
	range1.startHz = 6000000;
	range1.stopHz = 6500000;
	
	frequency_ranges_t range2;
	range2.maxPowerDBm = -59.02934938;
	range2.startHz = 6500000;
	range2.stopHz = 7000000;
	
	printf("asdasdasd\n"); fflush(stdout);
	
	FrequencyRangesCache &cache = FrequencyRangesCache::Instance();
	std::list<frequency_ranges_t *> ranges = cache.get(0, 0);	
	
	for (auto item : ranges) {
		printf("%lf  ", item->maxPowerDBm);
		printf("%d   ", item->startHz);
		printf("%d\n", item->stopHz);
	}
	
	cache.push(0, 0, &range1);
	cache.push(0, 0, &range2);
	
//	ranges = cache.get(0, 0);	
//	for (auto item : ranges) {
//		printf("%lf  ", item->maxPowerDBm);
//		printf("%d   ", item->startHz);
//		printf("%d\n", item->stopHz);
//	}
	
	
//	printf("distance %lf\n", utility::earth::distance(42.990967, -71.463767, 42.990967, -71.463767));
//
//	double destlat, destlon;
//	utility::earth::derived_position(53.3387462, -1.8874843, &destlat, &destlon, 30000, 270.0);
//	printf("new pos %lf    %lf\n", destlat, destlon);
	


	
	
	
	return 0;
}