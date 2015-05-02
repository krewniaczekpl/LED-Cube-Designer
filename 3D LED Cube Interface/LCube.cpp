#include "LCube.h"

//Public
LCube::LCube(scene::ISceneManager* sceneMgr) : _sceneMgr(sceneMgr), _noLightVisible(true){
	const float SEPERATION = 3.0f;
	const float OFFSET = SEPERATION / 2;
	const float CAM_X = 20.0f;

	_cubeNode = _sceneMgr->addEmptySceneNode(0, L_CUBE_ROOT);
	_onNode = _sceneMgr->addEmptySceneNode(_cubeNode, L_CUBE_ON);
	_offNode = _sceneMgr->addEmptySceneNode(_cubeNode, L_CUBE_ON);

	_camNode = _sceneMgr->addCameraSceneNode(0, core::vector3df(CAM_X, 0, 0), core::vector3df(0, 0, 0));
	
	_sceneMgr->setAmbientLight(video::SColorf(0.5f,0.5f,0.5f));
	_sceneMgr->addLightSceneNode(0, core::vector3df(CAM_X, 0, 0), video::SColorf(1,1,1), 10);

	int ledId = 0;
	//Create cube of spheres
	for(int y = LED_LAYERS / 2; y > -LED_LAYERS / 2; y--){

		for(int x = -(LED_X / 2); x < LED_X / 2; x++){
			for(int z = -(LED_Z / 2); z < LED_Z / 2; z++){
				scene::IMeshSceneNode* node = _sceneMgr->addSphereSceneNode(0.5f, 16, _offNode, ledId);
				node->setPosition(core::vector3df(x * SEPERATION + OFFSET, y * SEPERATION - OFFSET, z * SEPERATION + OFFSET));
				
				_ledStates.push_back(C_LED_OFF);
				_allNodes.push_back(node);

				ledId++;
			}
		}

	}

	//Marks the front of the cube
	_sceneMgr->addCubeSceneNode(1, _cubeNode, -1, core::vector3df(CAM_X / 2, -LED_LAYERS, 0));

	_cubeNode->setPosition(core::vector3df(0, 0, 6.5f));
}

void LCube::toggleNoLightVisible(){
	_noLightVisible = !_noLightVisible;
	_offNode->setVisible(_noLightVisible);
}

void LCube::screenClick(core::vector2di mousePos){
	scene::ISceneCollisionManager* collisionManager = _sceneMgr->getSceneCollisionManager();

	scene::ISceneNode* node = collisionManager->getSceneNodeFromScreenCoordinatesBB(mousePos);
	if(!node) return;

	int id = node->getID();
	
	if(id > -1)
		screenClickAction(id);
}

scene::ISceneNode* LCube::getNode(){
	return _cubeNode;
}

void LCube::reset(){
	for(size_t i = 0; i < _allNodes.size(); i++){
		_ledStates[i] = C_LED_OFF;
		_allNodes[i]->setParent(_offNode);
		setNodeColor(_allNodes[i], video::SColor(255, 255, 255, 255));
	}
}

void LCube::load(std::vector<int> ledStates){
	_ledStates = ledStates;

	for(size_t i = 0; i < _allNodes.size(); i++){
		_allNodes[i]->setParent((_ledStates[i] != C_LED_OFF) ? _onNode : _offNode);
		setNodeColor(_allNodes[i], _ledStates[i]);
	}
}

std::vector<int> LCube::getStates(){
	return _ledStates;
}

//Private
void LCube::setNodeColor(scene::ISceneNode* node, video::SColor color){
	_sceneMgr->getMeshManipulator()->setVertexColors(((scene::IMeshSceneNode*)node)->getMesh(), color);
}
void LCube::setNodeColor(scene::ISceneNode* node, int c){
	video::SColor color;
	switch(c){
	case C_LED_OFF:
		color = video::SColor(255, 255, 255, 255);
		break;
	case C_LED_RED:
		color = video::SColor(255, 255, 0, 0);
		break;
	case C_LED_GREEN:
		color = video::SColor(255, 0, 255, 0);
		break;
	case C_LED_BLUE:
		color = video::SColor(255, 0, 0, 255);
		break;
	case C_LED_YELLOW:
		color = video::SColor(255, 255, 255, 0);
		break;
	case C_LED_CYAN:
		color = video::SColor(255, 0, 255, 255);
		break;
	case C_LED_MAGENTA:
		color = video::SColor(255, 255, 0, 255);
		break;
	case C_LED_ON:
		color = _onColor;
	}

	setNodeColor(node, color);
}