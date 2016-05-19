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

#ifndef REQUEST_H
#define REQUEST_H


/* libcurl (http://curl.haxx.se/libcurl/c) */
#include <curl/curl.h>

#include "json.hpp"		// https://github.com/nlohmann/json

#include <iostream>
#include <cstdlib>
#include <string>


using JSON = nlohmann::json;



struct curl_answer_s {
	char *payload;
	size_t size;
};


class Request {
public:

	Request(std::string url)
	: m_Url(url) {
		this->m_Timeout = 5;
		this->m_MaxRedirect = 1;
	}

	Request(const Request& orig) {
	}

	virtual ~Request() {
		std::cout << "~Request(): " << this->m_Url << std::endl;
	}

	void	SetTimeout(int sec);
	void	SetMaxRedirect(int num);
	JSON	PostJSON(JSON data);

private:
	std::string	m_Url;

	int			m_Timeout;
	int			m_MaxRedirect;
	
	CURLcode	PerformPost(const char *data, struct curl_slist *headers, struct curl_answer_s *p_answer);
	CURLcode	PerformJSONPost(JSON obj, struct curl_answer_s *p_answer);
};



#endif /* REQUEST_H */

