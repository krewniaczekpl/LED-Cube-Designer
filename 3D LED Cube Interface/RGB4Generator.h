/*
	Created by Panagiotis Roubatsis
	Description: Generate aruino code for the
	4x4x4 RGB LED cube using the Rainbowduino board.
*/

#ifndef RGB_4_GENERATOR_H
#define RGB_4_GENERATOR_H

#include "3dledcubeint.h"
#include "LCodeGenerator.h"
#include "CubeData.h"

struct CompiledCubeFrameRGB4
{
	std::vector<std::string> colors;
	std::vector<core::vector3di> coords;

	int duration;
};

class RGB4Generator : public LCodeGenerator
{
private:
	std::vector<CompiledCubeFrameRGB4> _frames;

	core::vector3di resolveXYZ(int id);
	std::string colorEnumToString(int color);

	void compileAndAddFrame(CubeFrame frame);

public:
	RGB4Generator(CubeData* data);

	void arrayWrite(std::ostream& out);
	void compileAndWrite(std::ostream& out);
};

#endif