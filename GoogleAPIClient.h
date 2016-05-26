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

#include <iostream>
#include <cstdlib>
#include <string>

#include "json.hpp"		// https://github.com/nlohmann/json

#include "ASpectrumApiClient.h"
#include "enum.h"


using JSON = nlohmann::json;


BETTER_ENUM(DeviceType, char, FIXED, MODE_1, MODE_2);

class GoogleAPIClient : public ASpectrumApiClient {
public:
	
	GoogleAPIClient();
	GoogleAPIClient(double antenna_height, DeviceType type);
	virtual ~GoogleAPIClient();
	
	std::vector<SpectrumChannel> GetSpectrumChannels(double latitude, double longitude) override; // from ASpectrumApiClient
	std::string GetCurrentConfiguration() override; // from IConfiguration
	
private:
	
	std::vector<SpectrumChannel> JSONSpectrum2SpectrumChannels(JSON&& res);
	
	double m_AntennaHeight;
	std::string m_DeviceType;
	
	static std::string	m_GoogleSpectrumAPIKey;
	static unsigned int m_RequestCount;
};

#endif /* GOOGLEAPICLIENT_H */

