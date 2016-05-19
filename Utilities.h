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



#ifndef UTILITIES_H
#define UTILITIES_H

#include "Log.h"
#include <iostream>


#define FREE(x)   if (x != nullptr) { free(x); x = nullptr; }

#define DieWithError(exit_code, ...) do {\
		LogE(__VA_ARGS__);	\
		exit(exit_code); \
	} while(0)

#define DieWithErrno(exit_code) do {\
		LogERNO(); \
		exit(exit_code); \
	} while(0)

#endif /* UTILITIES_H */

