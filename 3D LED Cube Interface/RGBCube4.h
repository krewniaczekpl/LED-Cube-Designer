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
	Description: Used to design the 4x4x4
	Rainbowduino RGB cube.
*/

#ifndef RGB_CUBE_4_H
#define RGB_CUBE_4_H

#include "3dledcubeint.h"
#include "LCube.h"

//RGB cube Size 4x4x4
class RGBCube4 : public LCube{
protected:
	void screenClickAction(int id);
public:
	RGBCube4(scene::ISceneManager* sceneMgr);

	LCodeGenerator* getCodeGenerator(void* data);
	int getImporterEnum();
};

#endif