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
#include <errno.h>
#include <stdlib.h>
#include <stdarg.h>

#include "Log.h"



void Log::m_init(const char *filename) {
	size_t len = strlen(filename);
	m_Path = new char[len + 1];
	if (m_Path == nullptr) {
		fprintf(stderr, ERROR_HEADER "%s", strerror(errno));
	} else {
		strncpy(m_Path, filename, len);
		m_Path[len] = '\0';
	}
}

void Log::m_write(const char *fmt, va_list va_alist, bool onstderr) {
	if (onstderr) {
		va_list copy;
		va_copy(copy, va_alist);
		vfprintf(stderr, fmt, va_alist);
		fflush(stderr);
		va_end(copy);
	}
	if (m_Path != nullptr) {
		FILE *fp = fopen(m_Path, "a");
		if (fp != NULL) {
			vfprintf(fp, fmt, va_alist);			
			fflush(fp);
			fclose(fp);
		} else {
			fprintf(stderr, ERROR_HEADER "%s", strerror(errno));
			fflush(stderr);
		}
	} else if (!onstderr){
		vfprintf(stdout, fmt, va_alist);
		fflush(stdout);
	}
}

void Log::m_log(const char *fmt, ...) {
	va_list va_alist;
	
	if (fmt == NULL || strlen(fmt) == 0)
		return;
	
	va_start(va_alist, fmt);
	m_write(fmt, va_alist);
	va_end(va_alist);
}

void Log::m_debug(const char *header, const char *fmt, ...) {
#ifdef DEBUG
	va_list va_alist;
	
	if (fmt == NULL || strlen(fmt) == 0)
		return;

	
	va_start(va_alist, fmt);
	std::string format(std::string(header) + fmt);
	m_write(format.c_str(), va_alist);
	va_end(va_alist);
#endif
}

void Log::m_error(const char *header, const char* fmt, ...) {
	va_list va_alist;
	
	if (fmt == NULL || strlen(fmt) == 0)
		return;
	
	va_start(va_alist, fmt);
	std::string format(std::string(header) + fmt);
	m_write(format.c_str(), va_alist, true);
	va_end(va_alist);
}

void Log::m_hexdump(const void *addr, size_t len, const char *desc, ...) {
	size_t i;
	unsigned char buff[17];
	unsigned char *pc = (unsigned char*) addr;

	// Output description if given.
	if (desc != nullptr && strlen(desc) > 0) {
		va_list va_alist;
		va_start(va_alist, desc);
		m_write(desc, va_alist);
		va_end(va_alist);
		m_log(":\n");
	}

	// Process every byte in the data.
	for (i = 0; i < len; i++) {
		// Multiple of 16 means new line (with line offset).

		if ((i % 16) == 0) {
			// Just don't print ASCII for the zeroth line.
			if (i != 0)
				m_log("  %s\n", buff);

			// Output the offset.
			m_log("  %04x ", i);
		}

		// Now the hex code for the specific character.
		m_log(" %02x", pc[i]);

		// And store a printable ASCII character for later.
		if (isprint(pc[i]))
			buff[i % 16] = pc[i];
		else
			buff[i % 16] = '.';

		buff[(i % 16) + 1] = '\0';
	}

	// Pad out last line if not exactly 16 characters.
	while ((i % 16) != 0) {
		m_log("   ");
		i++;
	}

	// And print the final ASCII bit.
	m_log("  %s\n", buff);
}


