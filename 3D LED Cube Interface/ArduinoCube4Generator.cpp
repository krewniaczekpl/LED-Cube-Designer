#include "ArduinoCube4Generator.h"
#include <sstream>

const std::string arduinoProgram = "int ledPins[] = {0, 4, 8, 12, 1, 5, 9, 13, 2, 6, 10, A0, 3, 7, 11, A1};\n\
int groundPins[] = {A3, A5, A4, A2};\n\
const int COLS = 16;\n\
const int LAYERS = 4;\n\
word layersBuffer[] = {0x0000, 0x0000, 0x0000, 0x0000};\n\
const int FRAMES = ##FRAMECOUNT##;\n\
word frameBuffers[][4] = ##ARRAY##\n\
void setup(){\n\
  for(int i = 0; i < COLS; i++){\n\
    pinMode(ledPins[i], OUTPUT);\n\
    digitalWrite(ledPins[i], LOW);\n\
  }\n\
  for(int i = 0; i < LAYERS; i++){\n\
    pinMode(groundPins[i], OUTPUT);\n\
    digitalWrite(groundPins[i], HIGH);\n\
  }\n\
}\n\
void loop(){\n\
  ##ANIMATE##\n\
}\n\
void loadFrame(int index){\n\
  if(index >= 0 && index < FRAMES)\n\
    memcpy(layersBuffer, frameBuffers[index], sizeof(word)*4);\n\
}\n\
void drawBuffer(int iterations){\n\
  for(int i = 0; i < iterations; i++){\n\
   for(int layer = 0; layer < LAYERS; layer++){\n\
     for(int led = COLS - 1; led >= 0; led--){\n\
      digitalWrite(ledPins[COLS - 1 - led], bitRead(layersBuffer[layer], led));\n\
     }\n\
     digitalWrite(groundPins[layer], LOW);\n\
     delay(3);\n\
     digitalWrite(groundPins[layer], HIGH);\n\
    }\n\
  }\n\
}\n";

ArduinoCube4Generator::ArduinoCube4Generator(CubeData* data){
	data->updateCurrentFrame(-1);

	for(size_t i = 0; i < data->getFrameCount(); i++){
		compileAndAddFrame(data->getFrame(i));
	}
}

void ArduinoCube4Generator::compileAndAddFrame(CubeFrame frame){
	const int LAYER_BITS = LED_X * LED_Z;
	
	CompiledCubeFrame cFrame;

	for(int i = 0; i < LED_LAYERS; i++){

		std::bitset<LAYER_BITS> layer(0);
		for(int j = i * LAYER_BITS; j < i * LAYER_BITS + LAYER_BITS; j++){
			int bitIndex = (LAYER_BITS - 1) - (j - (i * LAYER_BITS));
			layer.set(bitIndex, frame.states[j] != C_LED_OFF);
		}
		cFrame.layers.push_back(layer);
		cFrame.duration = frame.duration;
	}

	_frames.push_back(cFrame);
}

void ArduinoCube4Generator::arrayWrite(std::ostream& out){
	out<<"{"<<std::endl;
	for(size_t i = 0; i < _frames.size(); i++){

		out<<"{";
		for(int j = 0; j < LED_LAYERS; j++){
			out<<"0x"<<std::hex<<short(_frames[i].layers[j].to_ullong());	//Change short to something else if it is more or less bits (eg. int for 32, long for 64)
			if(j != LED_LAYERS - 1) out<<",";
		}
		out<<"}";
		if(i != _frames.size() - 1) out<<","<<std::endl;
		
	}
	out<<std::endl<<"};"<<std::endl;
}

void ArduinoCube4Generator::compileAndWrite(std::ostream& out){
	std::stringstream arrStream;
	arrayWrite(arrStream);
	std::string ardArr = arrStream.str();
	
	char* cframeCount = new char[4];
	_itoa_s(_frames.size(), cframeCount, 4, 10);
	std::string frameCount(cframeCount);
	delete cframeCount;

	std::stringstream aniStream;
	for(size_t i = 0; i < _frames.size(); i++){
		aniStream<<"loadFrame("<<i<<");"<<std::endl;
		aniStream<<"drawBuffer("<<_frames[i].duration<<");"<<std::endl;
	}
	std::string animation = aniStream.str();

	std::string compProgram = arduinoProgram;

	int arr = compProgram.find("##ARRAY##");
	compProgram.replace(arr, 9, ardArr);

	int frc = compProgram.find("##FRAMECOUNT##");
	compProgram.replace(frc, 14, frameCount);

	int ani = compProgram.find("##ANIMATE##");
	compProgram.replace(ani, 11, animation);

	out<<compProgram;
}
