#include "CubeData.h"
#include <fstream>
#include <vector>
#include <cstdlib>

const int LED_COUNT = 64;	//4x4x4

CubeFrame createBlankRGBFrame()
{
	CubeFrame frame;
	frame.duration = 25;

	for(int i = 0; i < LED_COUNT; i++)
	{
		frame.states.push_back(C_LED_OFF);
	}

	return frame;
}

int getRGBDuration(std::string delayLine)
{
	std::string numStr = delayLine.substr(delayLine.find("(") + 1, delayLine.find(")") - delayLine.find("(") - 1);
	return atoi(numStr.c_str());
}

int getRGBEnumFromString(std::string color)
{
	//Primary Colors
	const std::string RED_STR = "FF0000";
	const std::string GREEN_STR = "00FF00";
	const std::string BLUE_STR = "0000FF";

	//Secondary Colors
	const std::string YELLOW_STR = "FFFF00";
	const std::string CYAN_STR = "00FFFF";
	const std::string MAGENTA_STR = "FF00FF";

	//Conversion of string to enum

	//Primary Colors
	if(color.find(RED_STR) != std::string::npos)
		return C_LED_RED;
	if(color.find(GREEN_STR) != std::string::npos)
		return C_LED_GREEN;
	if(color.find(BLUE_STR) != std::string::npos)
		return C_LED_BLUE;
	
	//Secondary Colors
	if(color.find(YELLOW_STR) != std::string::npos)
		return C_LED_YELLOW;
	if(color.find(CYAN_STR) != std::string::npos)
		return C_LED_CYAN;
	if(color.find(MAGENTA_STR) != std::string::npos)
		return C_LED_MAGENTA;

	return C_LED_OFF;
}

int getRGBIndexFromLine(std::string line)
{
	std::string indexStr = line.substr(line.find("/") + 2);
	return atoi(indexStr.c_str());
}

std::vector<CubeFrame> getRGBFrames(std::ifstream& file)
{
	std::vector<CubeFrame> frames;
	
	std::string line;
	while(line.find("loop()") == std::string::npos)
		std::getline(file, line);

	std::getline(file, line);

	//While rainbowduino program is still in the main loop
	while(line.find("}") == std::string::npos)
	{
		if(line.find("Rb.blankDisplay()") != std::string::npos)
			frames.push_back(createBlankRGBFrame());
		
		else if(line.find("delay(") != std::string::npos)
			frames[frames.size() - 1].duration = getRGBDuration(line);
		
		//Get color and index from line
		else if(line.find("Rb.setPixelZXY(") != std::string::npos)
		{
			int index = getRGBIndexFromLine(line);
			int color = getRGBEnumFromString(line);

			frames[frames.size() - 1].states[index] = color;
		}

		std::getline(file, line);
	}

	return frames;
}

void importCubeFromRainbow444RGBSource(CubeData* data, std::string filePath)
{
	std::ifstream file(removeQuotesFromPath(filePath));

	data->_frames = getRGBFrames(file);
	data->_ledCube->load(data->_frames[0].states);
	data->_currentFrame = 0;

	file.close();
}