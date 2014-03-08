/*
database.cpp
Copyright (C) 2013 celeron55, Perttu Ahola <celeron55@gmail.com>
*/

/*
This file is part of Freeminer.

Freeminer is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Freeminer  is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Freeminer.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "database.h"
#include "irrlichttypes.h"

static s32 unsignedToSigned(s32 i, s32 max_positive)
{
	if(i < max_positive)
		return i;
	else
		return i - 2*max_positive;
}

// modulo of a negative number does not work consistently in C
static s64 pythonmodulo(s64 i, s64 mod)
{
	if(i >= 0)
		return i % mod;
	return mod - ((-i) % mod);
}

long long Database::getBlockAsInteger(const v3s16 pos) {
	return (unsigned long long)pos.Z*16777216 +
		(unsigned long long)pos.Y*4096 + 
		(unsigned long long)pos.X;
}

v3s16 Database::getIntegerAsBlock(long long i) {
	s32 x = unsignedToSigned(pythonmodulo(i, 4096), 2048);
	i = (i - x) / 4096;
	s32 y = unsignedToSigned(pythonmodulo(i, 4096), 2048);
	i = (i - y) / 4096;
	s32 z = unsignedToSigned(pythonmodulo(i, 4096), 2048);
	return v3s16(x,y,z);
}
