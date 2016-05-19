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

#ifndef GOOGLEAPICLIENT_H
#define GOOGLEAPICLIENT_H


#include "json.hpp"		// https://github.com/nlohmann/json

#include <iostream>
#include <cstdlib>
#include <string>


using JSON = nlohmann::json;


class GoogleAPIClient {
public:
	static JSON PostAPI(double latitude, double longitude, double antenna_height);
	
	
private:
	static std::string	m_google_spectrum_api_key;
	static unsigned int m_request_count;
};

#endif /* GOOGLEAPICLIENT_H */

