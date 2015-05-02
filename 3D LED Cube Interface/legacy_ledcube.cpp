#include "legacy_ledcube.h"

LedCube::LedCube(scene::ISceneManager* sceneMgr) : _sceneMgr(sceneMgr), _noLightVisible(true){
	const float SEPERATION = 3.0f;
	const float OFFSET = SEPERATION / 2;
	const float CAM_X = 20.0f;

	_cubeNode = _sceneMgr->addEmptySceneNode(0, CubeNodeID::ROOT);
	_onNode = _sceneMgr->addEmptySceneNode(_cubeNode, CubeNodeID::ON);
	_offNode = _sceneMgr->addEmptySceneNode(_cubeNode, CubeNodeID::ON);

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
				
				_onLEDs.push_back(false);
				_allNodes.push_back(node);

				ledId++;
			}
		}

	}

	//Marks the front of the cube
	_sceneMgr->addCubeSceneNode(1, _cubeNode, -1, core::vector3df(CAM_X / 2, -LED_LAYERS, 0));

	_cubeNode->setPosition(core::vector3df(0, 0, 6.5f));
}

void LedCube::toggleNoLightVisible(){
	_noLightVisible = !_noLightVisible;
	_offNode->setVisible(_noLightVisible);
}

void LedCube::screenClick(core::vector2di mousePos){
	scene::ISceneCollisionManager* collisionManager = _sceneMgr->getSceneCollisionManager();

	scene::ISceneNode* node = collisionManager->getSceneNodeFromScreenCoordinatesBB(mousePos);
	if(!node) return;

	int id = node->getID();
	if(id > -1){
		_onLEDs[id] = !_onLEDs[id];
		node->setParent(_onLEDs[id] ? _onNode : _offNode);
		setNodeColor(node, _onLEDs[id] ? video::SColor(255, 255, 0, 0) : video::SColor(255, 255, 255, 255));
	}
}

void LedCube::reset(){
	for(int i = 0; i < _allNodes.size(); i++){
		_onLEDs[i] = false;
		_allNodes[i]->setParent(_offNode);
		setNodeColor(_allNodes[i], video::SColor(255, 255, 255, 255));
	}
}

void LedCube::load(std::vector<bool> LEDs){
	_onLEDs = LEDs;

	for(int i = 0; i < _allNodes.size(); i++){
		_allNodes[i]->setParent(_onLEDs[i] ? _onNode : _offNode);
		setNodeColor(_allNodes[i], _onLEDs[i] ? video::SColor(255, 255, 0, 0) : video::SColor(255, 255, 255, 255));
	}
}

scene::ISceneNode* LedCube::getNode(){
	return _cubeNode;
}

std::vector<bool> LedCube::getBits(){
	return _onLEDs;
}

//Private
void LedCube::setNodeColor(scene::ISceneNode* node, video::SColor color){
	_sceneMgr->getMeshManipulator()->setVertexColors(((scene::IMeshSceneNode*)node)->getMesh(), color);
}