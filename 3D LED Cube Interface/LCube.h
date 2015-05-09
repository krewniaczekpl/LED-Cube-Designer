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
	Description: Base class that handles the basic
	functionality of the on screen cube that is used
	to design/animate the physical cube.
*/

#ifndef L_CUBE_H
#define L_CUBE_H

#include "3dledcubeint.h"
#include "LCodeGenerator.h"
#include <vector>

enum{
	C_LED_OFF,
	C_LED_RED,
	C_LED_GREEN,
	C_LED_BLUE,
	C_LED_YELLOW,
	C_LED_CYAN,
	C_LED_MAGENTA,
	C_LED_ON	//Used if it is not an RGB Cube, otherwise only use the colours.
};

//Irrlicht IDs
enum{
	L_CUBE_ROOT = -10,	//Entire cube
	L_CUBE_ON = -20,	//Parts of the cube that are not off
	L_CUBE_OFF = -30	//Parts of the cube that are off
};

enum{
	IMPORTER_444,
	IMPORTER_444_RGB
};

class LCube{
private:
	scene::ISceneManager* _sceneMgr;
	scene::ICameraSceneNode* _camNode;	//Used for ray casting
	scene::ISceneNode* _cubeNode;		//Node to control the entire LED cube

	bool _noLightVisible;

protected:
	video::SColor _onColor;	//Color of LED that is in C_LED_ON state

	std::vector<int> _ledStates;
	std::vector<scene::ISceneNode*> _allNodes;

	scene::ISceneNode* _offNode;		//LEDs that are off
	scene::ISceneNode* _onNode;			//LEDs that are on

	//Set the color of a node
	void setNodeColor(scene::ISceneNode* node, video::SColor color);
	//Set the color of a node using C_LED enum values
	void setNodeColor(scene::ISceneNode* node, int c);

	//What to do when an element is clicked (Takes the Node ID as a parameter)
	virtual void screenClickAction(int id) = 0;

public:
	LCube(scene::ISceneManager* sceneMgr);
	virtual ~LCube(){}

	void toggleNoLightVisible();
	void screenClick(core::vector2di mousePos);

	//Returns the root scene node
	scene::ISceneNode* getNode();

	void reset();
	void load(std::vector<int> ledStates);

	std::vector<int> getStates();

	//Expects a pointer to the cube data
	virtual LCodeGenerator* getCodeGenerator(void* data) = 0;

	//Return code importer enum for use by CodeData's importCode() function
	virtual int getImporterEnum() = 0;
};

#endif