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