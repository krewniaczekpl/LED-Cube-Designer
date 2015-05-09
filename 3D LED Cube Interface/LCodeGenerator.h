/*
    Copyright (C) 2015 Panagiotis Roubatsis

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

/*
	Created by Panagiotis Roubatsis
	Description: Abstract class to define the
	items that need to be generated for a given
	cube.
*/

#ifndef L_CODE_GENERATOR_H
#define L_CODE_GENERATOR_H

#include "3dledcubeint.h"

#define ARDUINO_CUBE4_GENERATOR_ID 0xA444

class LCodeGenerator{
public:
	virtual void arrayWrite(std::ostream& out) = 0;
	virtual void compileAndWrite(std::ostream& out) = 0;

	virtual ~LCodeGenerator(){};
private:

};

#endif