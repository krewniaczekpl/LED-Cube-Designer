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
	Description: Stores and handles all the data such as
	the frames, and states of the cube. Also have an importing
	function, it reads previously exported arduino code and allows you
	to import the frames from it.
*/

#ifndef CUBE_DATA_H
#define CUBE_DATA_H

#include "3dledcubeint.h"
#include "LCube.h"
#include <string>
#include <vector>

struct CubeFrame{
	std::vector<int> states;
	int duration;
};

class CubeData{
private:
	std::vector<CubeFrame> _frames;
	int _currentFrame;

	LCube* _ledCube;

	//Add importer functions here as friend functions
	friend void importCubeFromArduino444Source(CubeData* data, std::string filePath);
	friend void importCubeFromRainbow444RGBSource(CubeData* data, std::string filePath);

public:
	CubeData();

	void addFrame(std::vector<int> frameStates);
	void addFrame(CubeFrame frame);

	void removeFrame(int frameIndex);

	void setCurrentFrame(int frameIndex);
	
	//Copies current frame from led cube bits
	void updateCurrentFrame(int iterations);

	void setLedCube(LCube* ledCube);

	//Uses the appropriate import function to parse
	//and load the code into this class.
	void importCode(std::string filePath);

	CubeFrame getFrame(int frameIndex);
	//Returns frame index as a wstring (Used to display frame number in listbox)
	std::vector<std::wstring> getFrameNames();
	//Number of frames.
	size_t getFrameCount();
	//Current frame.
	int getCurrentFrameIndex();
};

//Multiple use importer functions

//Code in Arduino444Importer.cpp
std::string removeQuotesFromPath(std::string filePath);

#endif