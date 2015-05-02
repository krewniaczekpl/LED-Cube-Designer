#include "RGB4Generator.h"
#include "LCube.h"

RGB4Generator::RGB4Generator(CubeData* data)
{
	data->updateCurrentFrame(-1);

	for(size_t i = 0; i < data->getFrameCount(); i++)
		compileAndAddFrame(data->getFrame(i));
}

//Public
void RGB4Generator::arrayWrite(std::ostream& out)
{
	for(size_t i = 0; i < _frames.size(); i++)
	{
		for(size_t item = 0; item < _frames[i].colors.size(); item++)
		{
			out<<"[("<<_frames[i].coords[item].X<<", "<<_frames[i].coords[item].Y<<", "<<_frames[i].coords[item].Z
				<<") "<<_frames[i].colors[item]<<"] ";
		}
		out<<std::endl;
	}
}

void RGB4Generator::compileAndWrite(std::ostream& out)
{
	out<<"#include <Rainbowduino.h>\n"
		<<"void setup(){\n"
		<<"Rb.init();\n"
		<<"}\n"
		<<"void loop(){\n";

	for(size_t i = 0; i < _frames.size(); i++)
	{
		out<<"Rb.blankDisplay();\n";
		for(size_t item = 0; item < _frames[i].colors.size(); item++)
		{
			if(_frames[i].colors[item].length() != 0)
			{
				out<<"Rb.setPixelZXY("
				<<_frames[i].coords[item].Z<<", "
				<<_frames[i].coords[item].X<<", "
				<<_frames[i].coords[item].Y<<", "
				<<_frames[i].colors[item]<<");"
				<<"//"<<item<<"\n";
			}
		}
		out<<"delay("<<_frames[i].duration<<");\n";
	}

	out<<"}\n";
}

//Private
void RGB4Generator::compileAndAddFrame(CubeFrame frame)
{
	CompiledCubeFrameRGB4 cFrame;
	for(size_t i = 0; i < frame.states.size(); i++)
	{
		cFrame.colors.push_back(colorEnumToString(frame.states[i]));
		cFrame.coords.push_back(resolveXYZ(i));
	}
	cFrame.duration = frame.duration;

	_frames.push_back(cFrame);
}

core::vector3di RGB4Generator::resolveXYZ(int id)
{
	int id2D = id % 16;
	return core::vector3di(3 - (id2D % 4), 3 - (id2D / 4), 3 - (id / 16));
}

std::string RGB4Generator::colorEnumToString(int color)
{
	//Primary Colors
	const std::string RED_STR = "0xFF0000";
	const std::string GREEN_STR = "0x00FF00";
	const std::string BLUE_STR = "0x0000FF";
	//Secondary Colors
	const std::string YELLOW_STR = "0xFFFF00";
	const std::string CYAN_STR = "0x00FFFF";
	const std::string MAGENTA_STR = "0xFF00FF";

	switch(color)
	{
	case C_LED_RED:
		return RED_STR;
	case C_LED_GREEN:
		return GREEN_STR;
	case C_LED_BLUE:
		return BLUE_STR;
	case C_LED_YELLOW:
		return YELLOW_STR;
	case C_LED_CYAN:
		return CYAN_STR;
	case C_LED_MAGENTA:
		return MAGENTA_STR;
	}
	return "";
}