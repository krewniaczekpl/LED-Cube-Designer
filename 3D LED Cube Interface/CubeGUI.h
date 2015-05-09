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
	Description: The GUI code for the side panel
	to add frames, and export code.
*/

#ifndef CUBE_GUI_H
#define CUBE_GUI_H

#include "3dledcubeint.h"
#include "CubeData.h"
#include "LCube.h"

class CubeGUI{
private:
	gui::IGUIEnvironment* _env;
	gui::IGUIListBox* _framesList;
	gui::IGUIEditBox* _exportFileBox;

	gui::IGUISpinBox* _iterationsSpinBox;

	LCube* _ledCube;
	CubeData _cubeData;

	int _lastFrame;	//Used to determine if led cube frame should be updated
					//built in irrlicht event is unreliable (doesn't register list change every time).

	void createArduinoCode();
	void createArduinoArray();

	void importCode();

	void setFrameNames(std::vector<std::wstring> names);

public:
	enum GUIID{
		ToggleShowHideBtn,
		ResetCubeBtn,
		AddFrameBtn,
		RemoveFrameBtn,
		ExportCodeBtn,
		ImportBtn,
		ShowArrayBtn,
		FrameLst,
		IterationsSpin
	};

	CubeGUI(gui::IGUIEnvironment* env, LCube* cube);

	//The button with the given id has been clicked
	void buttonClick(int id);

	void frameSelected();
};

#endif