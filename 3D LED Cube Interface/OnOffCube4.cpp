#include "OnOffCube4.h"
#include "ArduinoCube4Generator.h"

OnOffCube4::OnOffCube4(scene::ISceneManager* sceneMgr)
	: LCube(sceneMgr)
{
	_onColor = video::SColor(255, 255, 0, 0);
}

void OnOffCube4::screenClickAction(int id)
{
	scene::ISceneNode* node = _allNodes[id];

	_ledStates[id] = (_ledStates[id] == C_LED_OFF) ? C_LED_ON : C_LED_OFF;
	node->setParent(_ledStates[id] == C_LED_ON ? _onNode : _offNode);
	setNodeColor(node, _ledStates[id] == C_LED_ON ? C_LED_RED : C_LED_OFF);
}

LCodeGenerator* OnOffCube4::getCodeGenerator(void* data)
{
	return new ArduinoCube4Generator((CubeData*)data);
}

int OnOffCube4::getImporterEnum()
{
	return IMPORTER_444;
}