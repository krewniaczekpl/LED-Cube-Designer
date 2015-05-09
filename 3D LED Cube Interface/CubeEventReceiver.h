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
	Description: Handles events such as
	keyboard key presses and mouse click events.
	Handles gui events such as button clicks.
*/

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