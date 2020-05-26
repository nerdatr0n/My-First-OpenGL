#include "Input.h"
#include <freeglut.h>


CInput::CInput()
{
	for (int i = 0; i < 255; i++)
	{
		KeyState[i] = INPUT_UP;
	}
	// Sets up first input thing for Mouse
	for (int i = 0; i < 3; i++)
	{
		MouseState[i] = INPUT_UP;
	}
}



CInput::~CInput()
{
}


void CInput::Update()
{
	// Sets up first input thing for keybord
	for (int i = 0; i < 255; i++)
	{
		if (KeyState[i] == INPUT_FIRST_DOWN)
		{
			KeyState[i] = INPUT_DOWN;
		}
		else if (KeyState[i] == INPUT_FIRST_UP)
		{
			KeyState[i] = INPUT_UP;
		}
	}
	// Sets up first input thing for Mouse
	for (int i = 0; i < 3; i++)
	{
		if (MouseState[i] == INPUT_FIRST_DOWN)
		{
			MouseState[i] = INPUT_DOWN;
		}
		else if (MouseState[i] == INPUT_FIRST_UP)
		{
			MouseState[i] = INPUT_UP;
		}
	}
}


InputState CInput::GetKey(char _cKey)
{
	return KeyState[_cKey];
}

InputState CInput::GetMouse(int _iMouse)
{
	return MouseState[_iMouse];
}

glm::ivec2 CInput::GetMousePosition()
{
	return MousePosition;
}

void CInput::KeyboardDown(unsigned char key, int x, int y)
{
	if (KeyState[key] == INPUT_FIRST_UP or KeyState[key] == INPUT_UP)
	{
		KeyState[key] = INPUT_FIRST_DOWN;
	}
}



void CInput::KeyboardUp(unsigned char key, int x, int y)
{
	if (KeyState[key] == INPUT_FIRST_DOWN or KeyState[key] == INPUT_DOWN)
	{
		KeyState[key] = INPUT_FIRST_UP;
	}
}



void CInput::MouseClick(int button, int state, int x, int y)
{
	if (button >= 3)
	{
		return;
	}


	if (state == GLUT_DOWN and (MouseState[button] == INPUT_FIRST_UP or MouseState[button] == INPUT_UP))
	{
		MouseState[button] = INPUT_FIRST_DOWN;
	}
	if (state == GLUT_UP and (MouseState[button] == INPUT_FIRST_DOWN or MouseState[button] == INPUT_DOWN))
	{
		MouseState[button] = INPUT_FIRST_UP;
	}

}



void CInput::MousePassiveMove(int x, int y)
{
	MousePosition.x = x;

	// Makes the origin the bottom left
	MousePosition.y = Utils::SCR_HEIGHT - y;
}



void CInput::MouseMove(int x, int y)
{
	MousePosition.x = x;

	// Makes the origin the bottom left
	MousePosition.y = Utils::SCR_HEIGHT - y;
}


