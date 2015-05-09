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

#include "CubeEventReceiver.h"

CubeEventReceiver::CubeEventReceiver() : _gui(0){
	//Start with all keys up.
	for(int i = 0; i < KEY_KEY_CODES_COUNT; i++) _keysAreDown[i] = false;

	_mouseState.isLeftMouseDown = false;
}
void CubeEventReceiver::setGui(CubeGUI* gui){
	_gui = gui;
}

bool CubeEventReceiver::OnEvent(const SEvent& event){
	_mouseState.isLeftMouseDown = event.MouseInput.isLeftPressed();
	_mouseState.pos.X = event.MouseInput.X;
	_mouseState.pos.Y = event.MouseInput.Y;

	switch(event.EventType){
	case EET_KEY_INPUT_EVENT:
		_keysAreDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
		break;
	}

	if(_gui != 0 && event.EventType == EET_GUI_EVENT){
		switch(event.GUIEvent.EventType){
		case gui::EGET_BUTTON_CLICKED:
			_gui->buttonClick(event.GUIEvent.Caller->getID());
			break;
		case gui::EGET_LISTBOX_CHANGED:
			//_gui->frameSelected();
			break;
		}
	}

	return false;
}

bool CubeEventReceiver::isKeyDown(EKEY_CODE key){
	return _keysAreDown[key];
}

EMouseState CubeEventReceiver::getMouseState(){
	return _mouseState;
}