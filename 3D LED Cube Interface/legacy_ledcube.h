#ifndef LED_CUBE_H
#define LED_CUBE_H

#include "3dledcubeint.h"
#include <vector>

class LedCube{
private:
	std::vector<bool> _onLEDs;

	std::vector<scene::ISceneNode*> _allNodes;
	bool _noLightVisible;

	scene::ISceneManager* _sceneMgr;
	scene::ICameraSceneNode* _camNode;	//Used for ray casting
	scene::ISceneNode* _cubeNode;		//Node to control the entire LED cube
	scene::ISceneNode* _offNode;		//LEDs that are off
	scene::ISceneNode* _onNode;			//LEDs that are on

	//Set the color of a node
	void setNodeColor(scene::ISceneNode* node, video::SColor color);

	enum CubeNodeID{
		ROOT = -10,
		OFF = -20,
		ON = -30
	};
public:
	LedCube(scene::ISceneManager* sceneMgr);

	void toggleNoLightVisible();
	void screenClick(core::vector2di mousePos);
	scene::ISceneNode* getNode();

	//Load LEDs from boolean array
	void load(std::vector<bool> LEDs);

	//Reset all LEDs to off state
	void reset();

	std::vector<bool> getBits();
};

#endif