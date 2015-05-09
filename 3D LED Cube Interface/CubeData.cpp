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

#include "CubeData.h"
#include <cstdlib>

CubeData::CubeData(){
	_currentFrame = -1;

	//NULL pointer unless it is set later.
	_ledCube = 0;
}

void CubeData::addFrame(std::vector<int> frameStates){
	CubeFrame frame;
	frame.states = frameStates;
	frame.duration = 25;

	addFrame(frame);
}
void CubeData::addFrame(CubeFrame frame){
	_frames.push_back(frame);

	//Set the current frame as the one just added.
	setCurrentFrame(getFrameCount() - 1);
}

void CubeData::removeFrame(int frameIndex){
	if(getFrameCount() > 1){
		_frames.erase(_frames.begin() + frameIndex);
	}
	setCurrentFrame(0);
}

void CubeData::setCurrentFrame(int frameIndex){
	updateCurrentFrame(-1);

	_currentFrame = frameIndex;

	if(_ledCube != 0)
		_ledCube->load(_frames[_currentFrame].states);
}
void CubeData::updateCurrentFrame(int iterations){
	if(_currentFrame > -1){
		_frames[_currentFrame].states = _ledCube->getStates();

		if(iterations > -1)
			_frames[_currentFrame].duration = iterations;
	}
}

void CubeData::importCode(std::string fileName)
{
	int importer = 0;
	if(_ledCube != 0)
		importer = _ledCube->getImporterEnum();

	switch(importer)
	{
	case IMPORTER_444:
		importCubeFromArduino444Source(this, fileName);
		break;
	case IMPORTER_444_RGB:
		importCubeFromRainbow444RGBSource(this, fileName);
		break;
	default:
		importCubeFromArduino444Source(this, fileName);
		break;
	}
}

void CubeData::setLedCube(LCube* ledCube){
	_ledCube = ledCube;
	
	//Frame 0
	addFrame(_ledCube->getStates());
}

CubeFrame CubeData::getFrame(int frameIndex){
	return _frames[frameIndex];
}
std::vector<std::wstring> CubeData::getFrameNames(){
	std::vector<std::wstring> names;

	for(size_t i = 0; i < getFrameCount(); i++){
		char* cstr = new char[4];
		_itoa_s(i, cstr, 4, 10);
		std::string str(cstr);
		delete cstr;

		std::wstring wstr(str.begin(), str.end());
		names.push_back(wstr);
	}

	return names;
}

size_t CubeData::getFrameCount(){
	return _frames.size();
}
int CubeData::getCurrentFrameIndex(){
	return _currentFrame;
}