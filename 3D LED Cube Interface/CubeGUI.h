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