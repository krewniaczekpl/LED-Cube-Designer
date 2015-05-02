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