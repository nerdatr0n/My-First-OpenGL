#pragma once


namespace Utils
{

	const unsigned int SCR_WIDTH = 1024;
	const unsigned int SCR_HEIGHT = 512;
}


enum InputState
{
	INPUT_UP,
	INPUT_DOWN,
	INPUT_FIRST_UP,
	INPUT_FIRST_DOWN
};

enum Room
{
	SPLASH_SCREEN,
	MAIN_MENU,
	MAIN_LEVEL,
	GAME_OVER,
};


namespace Color
{
	const glm::vec3 offWhite = glm::vec3((float)236, (float)236, (float)236) * (float)(1 / 256);
	const glm::vec3 offBlack = glm::vec3((float)54, (float)54, (float)54) * (float)(1 / 256);
}


