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



#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Request.h"
#include "CurlGlobal.h"
#include "Log.h"
#include "Exceptions.h"
#include "Utilities.h"

Request::Request(std::string url)
: m_Url(url) {
	LogD(0, "Request(%s)", url.c_str());
	this->m_Timeout = 5;
	this->m_MaxRedirect = 1;
}

Request::~Request() {
	LogD(0, "~Request()");
}

void Request::SetTimeout(int sec) {
	LogD(0, "SetTimeout(%d)\n", sec);
	this->m_Timeout = sec;
}

void Request::SetMaxRedirect(int num) {
	LogD(0, "SetMaxRedirect(%d)\n", num);
	this->m_MaxRedirect = num;
}

size_t append_callback(void *contents, size_t size, size_t nmemb, void *p_answer) {
	LogD(0, "append_callback(*contents*, %d, %d, *p_answer*)\n", size, nmemb);
	size_t buffsize = size * nmemb;
	struct curl_answer_s *p = (struct curl_answer_s *) p_answer;

	char *tmp = (char *) realloc(p->payload, p->size + buffsize + 1);
	if (tmp == nullptr)
		DieWithErrno(1);

	p->payload = tmp;

	memcpy(&(p->payload[p->size]), contents, buffsize);
	p->size += buffsize;
	p->payload[p->size] = '\0';

	return buffsize;
}

CURLcode Request::PerformPost(const char *data, struct curl_slist *headers, struct curl_answer_s *p_answer) {
	LogD(0, "PerformPost(*data*, *headers*, *p_answer*)\n");
	CURL *curl_handle;
	CURLcode ret;

	// init the curl session
	curl_handle = curl_easy_init();
	if (curl_handle == nullptr)
		DieWithError(1, "Failed to create curl handle");

	// specify URL to get
	curl_easy_setopt(curl_handle, CURLOPT_URL, this->m_Url.c_str());

	// set post type request
	curl_easy_setopt(curl_handle, CURLOPT_CUSTOMREQUEST, "POST");

	// set accept and content type
	curl_easy_setopt(curl_handle, CURLOPT_HTTPHEADER, headers);

	// append json string
	curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDS, data);

	// send all data to this function
	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, append_callback);

	// pass our 'answer' struct to the callback function
	curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *) p_answer);

	// provide a user-agent field
	curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");

	// set timeout
	curl_easy_setopt(curl_handle, CURLOPT_TIMEOUT, this->m_Timeout);

	// enable location redirects
	curl_easy_setopt(curl_handle, CURLOPT_FOLLOWLOCATION, 1);

	// set maximum allowed redirects
	curl_easy_setopt(curl_handle, CURLOPT_MAXREDIRS, this->m_MaxRedirect);

	// get it!
	ret = curl_easy_perform(curl_handle);

	// cleanup curl stuff
	curl_easy_cleanup(curl_handle);

	return ret;
}

CURLcode Request::PerformJSONPost(JSON obj, struct curl_answer_s *p_answer) {
	LogD(0, "PerformJSONPost(*obj*, *p_answer*)\n");
	CURLcode ret;
	struct curl_slist *headers = nullptr;

	// set content type
	headers = curl_slist_append(headers, "Accept: application/json");
	headers = curl_slist_append(headers, "Content-Type: application/json");

	// perform post
	ret = this->PerformPost(obj.dump(-1).c_str(), headers, p_answer);

	// free headers
	curl_slist_free_all(headers);

	return ret;
}

JSON Request::PostJSON(JSON data) {
	LogD(0, "PostJSON(*data*)\n");
	CURLcode ret;
	struct curl_answer_s answer;

	// initialize answer struct
	answer.payload = nullptr;
	answer.size = 0;

	ret = this->PerformJSONPost(data, &answer);

	// check for errors
	if (ret != CURLE_OK) {
		LogE("curl_easy_perform() failed: %s\n", curl_easy_strerror(ret));
		if (answer.payload != nullptr)
			FREE(answer.payload);
		throw MakeException(CURLErrorException, curl_easy_strerror(ret));
	} else {
		try {
			JSON res = JSON::parse(answer.payload);
			FREE(answer.payload);

			return res;
		} catch (std::invalid_argument &e) {
			throw MakeException(JsonParseException, e.what());
		}
	}
}