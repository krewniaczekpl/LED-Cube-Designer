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
	Description: An application that allows the user
	to design an animation for an LED cube.
*/

#include "3dledcubeint.h"
#include "LCube.h"
#include "OnOffCube4.h"
#include "RGBCube4.h"
#include "CubeEventReceiver.h"
#include "CubeGUI.h"

#define BACKGROUND_COLOR 255, 75, 75, 75	//ARGB Format
#define WINDOW_SIZE 800, 600

const std::string welcomeMessage = "\
Welcome To The 3D LED Cube Interface!\n\
To move the cube around use the arrow keys.\n\
Enjoy creating designs and animations!\n";

//Creates a checkerboard background.
void checkerBoard(video::IImage* img, int width, int height);
//Resolve LED Cube type from an integer
LCube* resolveCubeType(scene::ISceneManager* sceneMgr, int choice);

int main(){
	//Ask for which cube to use
	system("cls");

	std::cout<<"Which cube would you like to design?"<<std::endl
		<<"1) 4x4x4 LED Cube (Arduino)"<<std::endl
		<<"2) 4x4x4 RGB Cube (Rainbowduino)"<<std::endl;

	int cubeChoice = 0;
	std::cin >> cubeChoice;
	//Flushes the std input stream
	std::cin.ignore();

	//Setup irrlicht
	system("cls");

	int lastTime, currentTime;
	float deltaTime;
	bool mouseClickLast = false;

	CubeEventReceiver events;	//Used to capture mouse and gui events
	IrrlichtDevice* device = createDevice(video::EDT_OPENGL, core::dimension2du(WINDOW_SIZE), 16, false, false, false, &events);
	if(!device){
		std::cout<<"ERROR - Can Not Initialize Device!"<<std::endl;
		return -1;
	}
	device->setWindowCaption(L"3D LED Cube - Designer (By: Panagiotis Roubatsis)");

	video::IVideoDriver* driver = device->getVideoDriver();
	scene::ISceneManager* sceneMgr = device->getSceneManager();
	gui::IGUIEnvironment* guiEnv = device->getGUIEnvironment();

	LCube* ledCube = resolveCubeType(sceneMgr, cubeChoice);

	//Used to rotate the cube
	float rotationY = 0.0f;
	float rotationZ = 0.0f;

	CubeGUI gui(guiEnv, ledCube);
	events.setGui(&gui);

	video::IImage* img = driver->createImage(video::ECF_A8R8G8B8, core::dimension2du(WINDOW_SIZE));
	checkerBoard(img, WINDOW_SIZE);
	video::ITexture* bgTexture = driver->addTexture("testImg", img);
	img->drop();

	system("cls");
	std::cout<<welcomeMessage<<std::endl;

	currentTime = device->getTimer()->getTime();
	while(device->run()){
		lastTime = currentTime;
		currentTime = device->getTimer()->getTime();
		deltaTime = (currentTime - lastTime) / 1000.0f;	//Calculate delta time and convert to seconds.
		
		//Screen click event for led cube
		if(events.getMouseState().isLeftMouseDown && !mouseClickLast){
			ledCube->screenClick(events.getMouseState().pos);
			mouseClickLast = true;
		}else if(!events.getMouseState().isLeftMouseDown){
			mouseClickLast = false;
		}
		gui.frameSelected();

		//Rotate cube using arrow keys
		if(events.isKeyDown(KEY_LEFT)){
			rotationY += 45 * deltaTime;
		}else if(events.isKeyDown(KEY_RIGHT)){
			rotationY -= 45 * deltaTime;
		}else if(events.isKeyDown(KEY_UP)){
			rotationZ -= 45 * deltaTime;
		}else if(events.isKeyDown(KEY_DOWN)){
			rotationZ += 45 * deltaTime;
		}else if(events.isKeyDown(KEY_NUMPAD0)){
			rotationZ = 0; rotationY = 0;
		}
		ledCube->getNode()->setRotation(core::vector3df(0, rotationY, rotationZ));

		//Draw gui and cube
		driver->beginScene(true, true, video::SColor(BACKGROUND_COLOR));
		driver->draw2DImage(bgTexture, core::recti(0, 0, 800, 600), core::recti(0, 0, 700, 500));
		sceneMgr->drawAll();
		guiEnv->drawAll();
		driver->endScene();
	}

	delete ledCube;
	device->drop();
}

void checkerBoard(video::IImage* img, int width, int height){
	const int SIZE = 100;
	for(int x = 0; x < width; x++){
		for(int y = 0; y < height; y++){
			if((x / SIZE) % 2 == 0 && (y / SIZE) % 2 == 0){
				img->setPixel(x, y, video::SColor(255, 0, 0, 0));
			}else{
				img->setPixel(x, y, video::SColor(255, 0, 25, 0));
			}
		}
	}
}

LCube* resolveCubeType(scene::ISceneManager* sceneMgr, int choice){
	switch(choice){
	case 1:
		return new OnOffCube4(sceneMgr);
	case 2:
		return new RGBCube4(sceneMgr);
	default:
		return new OnOffCube4(sceneMgr);
	}
}