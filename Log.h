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



#ifndef LOG_H
#define LOG_H



#include <string.h>
#include <string>
#include <utility>

#include "Singleton.h"
#include "Exceptions.h"


#define _STR(x)   #x
#define STR(x)   _STR(x)
#define __LOCATION__ __FILE__ ":" STR(__LINE__)

class Log : public Singleton<Log> {
public:

	Log() {
		m_Path = nullptr;
	}

	virtual ~Log() {
		if (m_Path != nullptr)
			delete[] m_Path;
	}
	
	// @override
	__PRE_FORCEINLINE__ static Log & Instance() __POST_FORCEINLINE__ {
		if (!ms_singleton)
			ms_singleton = new Log();
		assert(ms_singleton);
		return (*ms_singleton);
	}

	void m_init(const char *filename);
	void m_log(const char *fmt, ...);
	void m_debug(const char *header, const char *fmt, ...);
	void m_error(const char *header, const char *fmt, ...);
	void m_hexdump(const void *addr, size_t len, const char *desc, ...);

	
private:

	void m_write(const char *fmt, va_list va_alist, bool onstderr = false);

	char *m_Path;
};

#ifdef DEBUG
//#define WITH_COLORS
#ifdef WITH_COLORS
#define KNRM  "\x1B[0m"
#define KBOLD "\033[1m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
#define DEBUG_HEADER	KBOLD KYEL "[DEBUG](" __LOCATION__ ") " KNRM
#define ERROR_HEADER	KBOLD KRED "[ERROR](" __LOCATION__ ") " KNRM
#else
#define DEBUG_HEADER	"[DEBUG](" __LOCATION__ ") "
#define ERROR_HEADER	"[ERROR](" __LOCATION__ ") "
#endif
#else
#define ERROR_HEADER	"[ERROR](" __LOCATION__ ") "
#endif



#define LogINIT(filename)  Log::Instance().m_init(filename)

#ifndef LOG_LEVEL_MIN
#define LOG_LEVEL_MIN	1
#endif

#if defined(__clang__) || defined(__GNUC__)

#define LogL(lev, ...)	if (lev >= LOG_LEVEL_MIN) Log::Instance().m_log(__VA_ARGS__)
#ifdef DEBUG
#define LogD(lev, ...)	if (lev >= LOG_LEVEL_MIN) Log::Instance().m_debug(DEBUG_HEADER, __VA_ARGS__)
#endif
#define LogE(...)	Log::Instance().m_error(ERROR_HEADER, __VA_ARGS__)
#define LogHEXDUMP(addr, len, ...)	Log::Instance().m_hexdump(addr, len, __VA_ARGS__)

#endif

#ifndef DEBUG
#define LogD(...)
#endif

#define LogERNO() LogE("Error code: %d   Error message: %s\n", errno, strerror(errno))



#endif /* LOG_H */

