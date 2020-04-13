//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2020 Media Design School
//
// File Name   : GameManager.h
// Description : Header for Game Manager class
// Author      : David Haverland
// Mail        : david.hav8466@mediadesign.school.nz
//


#pragma once

#include <glew.h>
#include <freeglut.h>
#include <SOIL.h>
#include <iostream>
#include <fmod.hpp>
#include <vector>

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"


#include "ShaderLoader.h"
#include "camera.h"
#include "TextLabel.h"
#include "Mesh.h"



void RenderCallback();
void UpdateCallback();

enum InputState
{
	INPUT_UP,
	INPUT_DOWN,
	INPUT_FIRST_UP,
	INPUT_FIRST_DOWN
};


class GameManager
{
public:

	GameManager(int argc, char** argv);
	~GameManager();

	bool AudioInit();

	bool CreateSound(FMOD::Sound* _sound, const CHAR* _fileLocation);

	void CreateTexture(GLuint* _texture, const CHAR* _fileLocation);



	void Render();
	void Update();
	void KeyboardInput();

	void KeyboardDown(unsigned char key, int x, int y);

	void KeyboardUp(unsigned char key, int x, int y);

private:

	InputState KeyState[255];
	TextLabel* Text;

	GLuint program;
	GLfloat currentTime;

	GLuint texture01;
	GLuint texture02;

	GLuint VAO;
	GLuint EBO;
	GLuint VBO;

	CCamera* m_pCamera;

	// Audio
	FMOD::System* audioSystem;
	FMOD::Sound* fxThump;
	FMOD::Sound* trackBackground;

	// Camera Variables
	glm::vec3 camPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 camLookDir = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 camUpDir = glm::vec3(0.0f, 1.0f, 0.0f);

	// Screen/Viewport size
	const unsigned int SCR_WIDTH = Utils::SCR_WIDTH;
	const unsigned int SCR_HEIGHT = Utils::SCR_HEIGHT;

	std::vector<CMesh*> m_vecObjects;
	
};


