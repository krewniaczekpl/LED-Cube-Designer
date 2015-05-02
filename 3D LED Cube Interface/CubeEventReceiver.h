#ifndef CUBE_EVENT_RECEIVER_H
#define CUBE_EVENT_RECEIVER_H

#include "3dledcubeint.h"
#include "CubeGUI.h"

struct EMouseState{
		core::vector2di pos;
		bool isLeftMouseDown;
};

class CubeEventReceiver : public IEventReceiver{
private:
	bool _keysAreDown[KEY_KEY_CODES_COUNT];
	EMouseState _mouseState;

	CubeGUI* _gui;

public:
	CubeEventReceiver();

	//IEventReceiver override. It receives the events from irrlicht (Keyboard and GUI).
	bool OnEvent(const SEvent& event);
	void setGui(CubeGUI* gui);

	bool isKeyDown(EKEY_CODE key);
	EMouseState getMouseState();
};

#endif