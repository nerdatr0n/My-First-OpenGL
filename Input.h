#pragma once

#include "glm.hpp"
#include "Utility.h"

class CInput
{
public:
	CInput();
	~CInput();

	//glm::vec2 GetMouseCoord();
	//bool GetMouseInput();

	InputState GetKey(char _cKey);
	InputState GetMouse(int _iMouse);
	glm::ivec2 GetMousePosition();

	void KeyboardDown(unsigned char key, int x, int y);
	void KeyboardUp(unsigned char key, int x, int y);
	void MouseClick(int button, int state, int x, int y);
	void MousePassiveMove(int x, int y);
	void MouseMove(int x, int y);

	void Update();


private:

	InputState KeyState[255];
	InputState MouseState[3];
	glm::ivec2 MousePosition;
};

