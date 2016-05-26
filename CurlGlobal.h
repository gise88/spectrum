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

#ifndef CURLGLOBAL_H
#define CURLGLOBAL_H

/* libcurl (http://curl.haxx.se/libcurl/c) */
#include <curl/curl.h>
#include "Log.h"

#include "Singleton.h"

class CurlGlobal : public Singleton<CurlGlobal> {
public:

	CurlGlobal() {
		LogD(0, "CurlGlobal()\n");
		// sets up the program environment that libcurl needs
		curl_global_init(CURL_GLOBAL_ALL);
	}

	virtual ~CurlGlobal() {
		LogD(0, "~CurlGlobal()\n");
		// we're done with libcurl, so clean it up
		curl_global_cleanup();
	}
};


// global singleton instance of Log class
static CurlGlobal gs_instance_curlglobal;



#endif /* CURLGLOBAL_H */

