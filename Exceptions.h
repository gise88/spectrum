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


class JsonParseException : public std::exception {
	char* m_text;
public:

	JsonParseException(const char* text) {
		m_text = new char[strlen(text) + 1];
		strcpy(m_text, text);
	}

	~JsonParseException() throw () {
		delete[] m_text;
	}

	const char* what() const noexcept {
		return m_text;
	}
};


class CURLErrorException : public std::exception {
	char* m_text;
public:

	CURLErrorException(const char* text) {
		m_text = new char[strlen(text) + 1];
		strcpy(m_text, text);
	}

	~CURLErrorException() throw () {
		delete[] m_text;
	}

	const char* what() const noexcept {
		return m_text;
	}
};



#endif /* EXCEPTIONS_H */

