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