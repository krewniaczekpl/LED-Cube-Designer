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