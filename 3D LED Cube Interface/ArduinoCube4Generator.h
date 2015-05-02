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