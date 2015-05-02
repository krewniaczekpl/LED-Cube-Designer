#include "CubeData.h"
#include <fstream>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <bitset>
#include <regex>

std::vector<int> getFrameIterations(std::ifstream& file){
	std::vector<int> frames;

	while(!file.eof()){
		std::string line;
		getline(file, line);

		if(std::regex_search(line.begin(), line.end(), std::tr1::regex("drawBuffer\\(\\d.+\\)"))){
			std::string iterStr = line.substr(line.find("(") + 1, line.find(")") - line.find("(") - 1);
			frames.push_back(atoi(iterStr.c_str()));
		}
	}

	file.clear();
	file.seekg(0, std::ios::beg);
	return frames;
}

std::vector<std::string> tokenizeByDelimiter(std::string in, char delim){
	std::vector<std::string> tokens;
	std::stringstream ss(in);
	
	std::string token;
	while(!ss.eof()){
		getline(ss, token, delim);
		tokens.push_back(token);
	}

	return tokens;
}
unsigned short htoi(std::string sHex){
	std::stringstream ss;
	sHex = sHex.substr(2, sHex.length() - 2);	//Remove 0x from the front
	
	ss << std::hex << sHex;
	unsigned short x;
	ss >> x;

	return x;
}

std::vector<CubeFrame> getFrames(std::ifstream& file){
	std::vector<CubeFrame> frames;
	std::vector<int> iter = getFrameIterations(file);
	
	std::string line;
	while(line != "word frameBuffers[][4] = {")
		getline(file, line);
	getline(file, line);
	
	int frameIndex = 0;
	do{
		line = line.substr(1, line.find("}") - 1);
		std::vector<std::string> strHexNums = tokenizeByDelimiter(line, ',');
		std::vector<unsigned short> nums;
		
		for(size_t i = 0; i < strHexNums.size(); i++)
			nums.push_back(htoi(strHexNums[i]));

		CubeFrame frame;
		for(size_t i = 0; i < nums.size(); i++){
			std::bitset<16> b(nums[i]);
			
			for(size_t j = b.size() - 1; j > 0; j--)
				frame.states.push_back(b[j] ? C_LED_ON : C_LED_OFF);
			frame.states.push_back(b[0] ? C_LED_ON : C_LED_OFF);
		}

		frame.duration = iter[frameIndex];
		frames.push_back(frame);

		frameIndex++;
		getline(file, line);
	}while(line != "};");

	file.clear();
	file.seekg(0, std::ios::beg);
	return frames;
}

std::string removeQuotesFromPath(std::string filePath){
	if(filePath.length() == 0) return "";
	if(filePath[0] != '\"')
		return filePath[0] + removeQuotesFromPath(filePath.substr(1, filePath.length() - 1));
	else return removeQuotesFromPath(filePath.substr(1, filePath.length() - 1));
}

//Function defined in CubeData.h
void importCubeFromArduino444Source(CubeData* data, std::string filePath){
	std::ifstream file(removeQuotesFromPath(filePath));

	data->_frames = getFrames(file);
	data->_ledCube->load(data->_frames[0].states);
	data->_currentFrame = 0;
	
	file.close();
}
