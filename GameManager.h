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

#include "camera.h"

void RenderCallback();
void UpdateCallback();


class GameManager
{
public:

	GameManager(int argc, char** argv);
	~GameManager();

	void CreateTexture(GLuint* _texture, const CHAR* _fileLocation);



	void Render();
	void Update();

private:
	GLuint program;
	GLfloat currentTime;

	GLuint texture01;
	GLuint texture02;

	GLuint VAO;
	GLuint EBO;
	GLuint VBO;

	CCamera* Camera;

	// Audio
	FMOD::System* audioSystem;
	FMOD::Sound fxThump;
	FMOD::Sound trackBackground;

	// Camera Variables
	glm::vec3 camPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 camLookDir = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 camUpDir = glm::vec3(0.0f, 1.0f, 0.0f);

	// Screen/Viewport size
	const unsigned int SCR_WIDTH = 800;
	const unsigned int SCR_HEIGHT = 800;

};

