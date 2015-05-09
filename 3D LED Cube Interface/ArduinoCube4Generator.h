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
	Description: Generates arduino code
	for the 4x4x4 standard LED cube.
*/

#ifndef ARDUINO_CUBE_4_GENERATOR_H
#define ARDUINO_CUBE_4_GENERATOR_H

#include "3dledcubeint.h"
#include "LCodeGenerator.h"
#include "CubeData.h"
#include <iostream>
#include <vector>
#include <bitset>

struct CompiledCubeFrame{
	std::vector<std::bitset<LED_X * LED_Z> > layers;	//For the 4x4x4 cube bitset must be 16 (16bits per layer)
	int duration;
};

//Code Generator for 4x4x4 OnOff Cube
class ArduinoCube4Generator : public LCodeGenerator{
private:
	std::vector<CompiledCubeFrame> _frames;
	
	void compileAndAddFrame(CubeFrame frame);
public:
	ArduinoCube4Generator(CubeData* data);
	void arrayWrite(std::ostream& out);
	void compileAndWrite(std::ostream& out);
};

#endif