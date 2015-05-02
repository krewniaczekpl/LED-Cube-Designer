#include "RGBCube4.h"
#include "RGB4Generator.h"

RGBCube4::RGBCube4(scene::ISceneManager* sceneMgr)
	: LCube(sceneMgr)
{
	_onColor = video::SColor(255, 255, 0, 0);
}

void RGBCube4::screenClickAction(int id)
{
	scene::ISceneNode* node = _allNodes[id];
	int state = _ledStates[id];
	state++;

	if(state > C_LED_MAGENTA){
		_ledStates[id] = C_LED_OFF;
	}else{
		_ledStates[id] = state;
	}

	node->setParent(_ledStates[id] != C_LED_OFF ? _onNode : _offNode);
	setNodeColor(node, _ledStates[id]);
}

LCodeGenerator* RGBCube4::getCodeGenerator(void* data)
{
	return new RGB4Generator((CubeData*)data);
}

int RGBCube4::getImporterEnum()
{
	return IMPORTER_444_RGB;
}