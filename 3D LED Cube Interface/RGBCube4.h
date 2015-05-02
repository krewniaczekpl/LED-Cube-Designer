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