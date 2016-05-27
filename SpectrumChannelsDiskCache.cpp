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

#include <iomanip>
#include <fstream>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "Log.h"
#include "Exceptions.h"
#include "SpectrumConstants.h"
#include "SpectrumChannelsDiskCache.h"


void SpectrumChannelsDiskCache::EnsureCacheFolder() {
	LogD(0, "EnsureCacheFolder()\n");
	struct stat sb;	
	int ret = stat(CACHE_FILES_FOLDER, &sb);
	
	if (ret == 0 && !S_ISDIR(sb.st_mode))
		throw MakeException(std::invalid_argument, "The file \"" CACHE_FILES_FOLDER "\" already exist but it is not a folder");
	
	if (ret == -1) {
		ret = mkdir(CACHE_FILES_FOLDER, 0700);
		LogD(0, "mkdir %s   returned %d\n", CACHE_FILES_FOLDER, ret);
		if (ret != 0)
			throw MakeException(std::invalid_argument, "Cannot create the folder " CACHE_FILES_FOLDER);
	}
}

SpectrumChannelsDiskCache::SpectrumChannelsDiskCache(std::string config_folder) {
	LogD(0, "SpectrumChannelsDiskCache(%s)\n", config_folder.c_str());
	
	struct stat sb;
	m_CacheFolder = CACHE_FILES_FOLDER + config_folder + "/";
	
	int ret = stat(m_CacheFolder.c_str(), &sb);
	
	if (ret == 0 && !S_ISDIR(sb.st_mode))
		throw MakeException(std::invalid_argument, "The file \"" + config_folder + "\" already exist but it is not a folder");
	
	if (ret == -1) {
		ret = mkdir(m_CacheFolder.c_str(), 0700);
		LogD(0, "mkdir %s   returned %d\n", m_CacheFolder.c_str(), ret);
		if (ret != 0)
			throw MakeException(std::invalid_argument, "Cannot create the folder " + m_CacheFolder);
	}
}

SpectrumChannelsDiskCache::~SpectrumChannelsDiskCache() {
	LogD(0, "~SpectrumChannelsDiskCache()\n");
}

void SpectrumChannelsDiskCache::LoadData(
		// Lambda function: check if the filename contains a coordinate,
		// checks if the coordinate fits in the current working area and if so
		// returns true and fills the idx_x, idx_y, otherwise returns false.
		std::function<bool(char *, uint &, uint &)> foreach_file, 
		// Lambda function: pass the vector of SpectrumChannel and x,y index of cache matrix
		std::function<void(uint, uint, std::vector<SpectrumChannel>&)> foreach_channel_read) {
	LogD(0, "LoadData()\n");

	DIR *dir;
	struct dirent *ent;
	struct stat sb;
	
	LogD(0, "trying to open directory: %s\n", m_CacheFolder.c_str());
	if ((dir = opendir(m_CacheFolder.c_str())) != NULL) {
		while ((ent = readdir(dir)) != NULL) {
			std::string current = m_CacheFolder + ent->d_name;
			int ret = stat(current.c_str(), &sb);
			if (ret == 0 && S_ISREG(sb.st_mode)) {
				uint idx_x, idx_y;
				bool needed = foreach_file(ent->d_name, idx_x, idx_y);
				LogD(0, "file %s is%s needed\n", ent->d_name, needed?"":" not");
				if (needed) {
					LogD(0, "loading data in -> idx_x: %d  idx_y: %d\n", idx_x, idx_y);
					uint channel_num;
					double max_power_db;
					std::string line;
					std::ifstream infile(current);
					std::vector<SpectrumChannel> vec;
					while (std::getline(infile, line)) {
						if (sscanf(line.c_str(), "%d,%lf", &channel_num, &max_power_db) == 2) {
							vec.push_back(SpectrumChannel(channel_num, max_power_db));
							LogD(0, "idx_x: %d  idx_y: %d   - %d   %.15lf\n", idx_x, idx_y, channel_num, max_power_db);
						}
					}
					if (vec.size() > 0)
						foreach_channel_read(idx_x, idx_y, vec);
				}
			}
		}
		closedir(dir);
	}
}

void SpectrumChannelsDiskCache::WriteData(double lat, double lng, std::vector<SpectrumChannel>& vec) {
	LogD(0, "WriteData(*vec*, %lf, %lf)\n", lat, lng);
	std::string filename(m_CacheFolder + std::to_string(lat) + "," + std::to_string(lng) + ".csv");
	LogL(5, "write data on file: %s\n", filename.c_str());
	
	std::ofstream ofs(filename);	
	for(SpectrumChannel item : vec)
		ofs << item.number << "," << std::setprecision(15) << item.maxPowerDBm << std::endl;
	ofs.close();
}