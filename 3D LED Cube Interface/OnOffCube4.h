/*
	Created by Panagiotis Roubatsis
	Description: Used to design the 4x4x4
	standard cube.
*/

#ifndef ON_OFF_CUBE_4_H
#define ON_OFF_CUBE_4_H

#include "3dledcubeint.h"
#include "LCube.h"
#include "LCodeGenerator.h"
#include "CubeData.h"

//Standard on or off cube Size 4x4x4
class OnOffCube4 : public LCube{
protected:
	void screenClickAction(int id);
public:
	OnOffCube4(scene::ISceneManager* sceneMgr);
	
	LCodeGenerator* getCodeGenerator(void* data);
	int getImporterEnum();
};

#endif