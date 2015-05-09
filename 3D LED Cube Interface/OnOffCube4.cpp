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