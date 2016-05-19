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
 * File:   definitions.h
 * Author: Gianluca Iselli <gianluca.iselli@gmail.com>
 *
 * Created on May 15, 2016, 4:19 PM
 */

#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#if defined(__GNUC__) || defined(__clang__)
#define __PRE_FORCEINLINE__			inline 
#define __POST_FORCEINLINE__		__attribute__((always_inline))
#define __FUNC_FORCE_INLINE__		__attribute__((always_inline))
#endif

#if _WIN32 || _WIN64
#if _WIN64
#define ENVIRONMENT64
#else
#define ENVIRONMENT32
#endif
#endif

// Check GCC
#if __GNUC__
#if __x86_64__ || __ppc64__
#define ENVIRONMENT64
#else
#define ENVIRONMENT32
#endif
#endif




#endif /* DEFINITIONS_H */

