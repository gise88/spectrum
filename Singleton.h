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



#ifndef SINGLETON_H
#define SINGLETON_H

#include <assert.h>

#include "definitions.h"



template <typename T> class Singleton {
public:

	Singleton() {
		assert(!ms_singleton);
		ulong offset = (ulong) (T*) 1 - (ulong) (Singleton <T>*) (T*) 1;
		ms_singleton = (T*) ((ulong) this +offset);
	}

	virtual ~Singleton() {
		assert(ms_singleton);
		ms_singleton = 0;
	}

	__PRE_FORCEINLINE__ static T & Instance() __POST_FORCEINLINE__ {
		assert(ms_singleton);
		return (*ms_singleton);
	}

	__PRE_FORCEINLINE__ static T * InstancePtr() __POST_FORCEINLINE__ {
		return (ms_singleton);
	}

	__PRE_FORCEINLINE__ static T & instance() __POST_FORCEINLINE__ {
		assert(ms_singleton);
		return (*ms_singleton);
	}
	
	
private:
	static T * ms_singleton;
};

template <typename T> T * Singleton <T>::ms_singleton = 0;

#endif /* SINGLETON_H */

