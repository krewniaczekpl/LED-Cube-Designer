#include "CubeGUI.h"
#include "ArduinoCube4Generator.h"
#include <fstream>

CubeGUI::CubeGUI(gui::IGUIEnvironment* env, LCube* cube) : _env(env), _ledCube(cube){
	_cubeData.setLedCube(cube);
	_lastFrame = 0;

	//Make sure to place a bitmap font in this folder
	env->getSkin()->setFont(env->getFont("fonts/arial.xml"));

	gui::IGUITabControl* tabs = env->addTabControl(core::recti(10, 10, 300, 590), 0, true, true);
	gui::IGUITab* optionsTab = tabs->addTab(L"Options");
	gui::IGUITab* exportTab = tabs->addTab(L"Export/Import");

	//Options
	env->addButton(core::recti(10, 10, 250, 60), optionsTab, ToggleShowHideBtn, L"Show/Hide Off LEDs");
	env->addButton(core::recti(10, 75, 250, 125), optionsTab, ResetCubeBtn, L"Reset Cube");
	
	_framesList = env->addListBox(core::recti(10, 140, 250, 300), optionsTab, FrameLst);
	_framesList->addItem(L"0");

	env->addButton(core::recti(10, 310, 250, 350), optionsTab, AddFrameBtn, L"Add Frame");
	env->addButton(core::recti(10, 360, 250, 400), optionsTab, RemoveFrameBtn, L"Remove Frame");
	
	env->addStaticText(L"Iterations:", core::recti(10, 415, 250, 445), false, true, optionsTab);
	_iterationsSpinBox = env->addSpinBox(L"Iterations", core::recti(10, 450, 250, 480), true, optionsTab, IterationsSpin);
	_iterationsSpinBox->setRange(1, 1000);
	_iterationsSpinBox->setValue(25);

	//Export / Import
	env->addButton(core::recti(10, 10, 250, 60), exportTab, ShowArrayBtn, L"Show Array");
	env->addButton(core::recti(10, 75, 250, 125), exportTab, ExportCodeBtn, L"Export Arduino Code");
	_exportFileBox = env->addEditBox(L"stdout", core::recti(10, 140, 250, 190), true, exportTab);

	env->addButton(core::recti(10, 200, 250, 300), exportTab, ImportBtn, L"Import Arduino\nSource Code");
}

void CubeGUI::buttonClick(int id){
	switch(id){
		//Options
	case ToggleShowHideBtn:
		_ledCube->toggleNoLightVisible();
		break;
	case ResetCubeBtn:
		_ledCube->reset();
		break;
	case AddFrameBtn:
		_cubeData.updateCurrentFrame(-1);
		_cubeData.addFrame(_cubeData.getFrame(_cubeData.getCurrentFrameIndex()));
		setFrameNames(_cubeData.getFrameNames());
		break;
	case RemoveFrameBtn:
		if(_framesList->getSelected() > -1){
			_cubeData.removeFrame(_framesList->getSelected());
			setFrameNames(_cubeData.getFrameNames());
		}
		break;
	case ImportBtn:
		importCode();
		break;

		//Export
	case ShowArrayBtn:
		createArduinoArray();
		break;
	case ExportCodeBtn:
		createArduinoCode();
		break;
	}
}
void CubeGUI::frameSelected(){
	int frameIndex = _framesList->getSelected();
	if(frameIndex > -1 && _lastFrame != frameIndex){
		_cubeData.updateCurrentFrame((int)_iterationsSpinBox->getValue());
		_cubeData.setCurrentFrame(frameIndex);

		_iterationsSpinBox->setValue((irr::f32)_cubeData.getFrame(frameIndex).duration);

		_lastFrame = frameIndex;
	}
}

//Private
void CubeGUI::createArduinoCode(){
	LCodeGenerator* codeGen = _ledCube->getCodeGenerator(&_cubeData);

	std::wstring file = _exportFileBox->getText();
	
	if(file == L"stdout"){
		codeGen->compileAndWrite(std::cout);
	}
	else{
		system("mkdir export");
		std::ofstream out(L"export/" + file + L".ino");
		codeGen->compileAndWrite(out);
		out.close();
		std::cout<<"Export Complete!"<<std::endl;
	}

	delete codeGen;
}
void CubeGUI::createArduinoArray(){
	LCodeGenerator* codeGen = _ledCube->getCodeGenerator(&_cubeData);
	codeGen->arrayWrite(std::cout);
	delete codeGen;
}

void CubeGUI::setFrameNames(std::vector<std::wstring> names){
	_framesList->clear();
	for(size_t i = 0; i < names.size(); i++) _framesList->addItem(names[i].c_str());
}

void CubeGUI::importCode(){
	std::string filePath;
	
	system("cls");
	std::cout<<"Drag & Drop The File Into The Command Prompt And Hit Enter..."<<std::endl;
	getline(std::cin, filePath);

	_cubeData.importCode(filePath);

	//Update Frames In List View
	setFrameNames(_cubeData.getFrameNames());
	//Update Iteration Count For The First Frame in the Spin Box
	_iterationsSpinBox->setValue((irr::f32)_cubeData.getFrame(0).duration);
}