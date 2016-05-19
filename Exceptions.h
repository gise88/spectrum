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
 * File:   Exceptions.h
 * Author: Gianluca Iselli <gianluca.iselli@gmail.com>
 *
 * Created on May 6, 2016, 1:04 AM
 */

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <iostream>       // std::cout
#include <exception>      // std::exception
#include <cstring>        // std::strlen, std::strcpy
#include <stdexcept>
#include "Log.h"




#define EXCEPTION_HEADER	"[EXCEPTION](" __LOCATION__ ") "
#define MakeException(type, text)\
		type(std::string(EXCEPTION_HEADER) + text)


class JsonParseException : public std::exception {
	char* m_Text;
public:

	JsonParseException(std::string text) {
		m_Text = new char[text.length() + 1];
		strcpy(m_Text, text.c_str());
	}

	~JsonParseException() throw () {
		delete[] m_Text;
	}

	const char* what() const noexcept {
		return m_Text;
	}
};


class CURLErrorException : public std::exception {
	char* m_Text;
public:

	CURLErrorException(std::string text) {
		m_Text = new char[text.length() + 1];
		strcpy(m_Text, text.c_str());
	}

	~CURLErrorException() throw () {
		delete[] m_Text;
	}

	const char* what() const noexcept {
		return m_Text;
	}
};



#endif /* EXCEPTIONS_H */

