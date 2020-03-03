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



class GameManager
{
public:

	GameManager(int argc, char** argv);
	~GameManager();



	void Render();
	void Update();

private:
	GLuint program;
	GLfloat currentTime;

	GLuint texture;

	GLuint VAO;
	GLuint EBO;
	GLuint VBO;


	// EVERYTHING BELOW THIS SHOULD BE REMOVED AT SOME POINT
	GLfloat vertices[]
	{
		// Position				// Color			// Texture Coords
		-4.0f,  5.0f, 0.0f,		1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // Top - Left
		-6.5f,  0.0f, 0.0f,		1.0f, 0.0f, 0.0f,	-0.2f, 0.5f, // Mid - Left
		-4.0f, -5.0f, 0.0f,		0.0f, 1.0f, 0.0f,	0.0f, 1.0f, // Bot - Left
		 4.0f, -5.0f, 0.0f,		1.0f, 1.0f, 0.0f,	1.0f, 1.0f, // Top - Right
		 6.5f,  0.0f, 0.0f,		1.0f, 1.0f, 0.0f,	0.0f, 0.0f, // Mid - Right
		 4.0f,  5.0f, 0.0f,		0.0f, 0.0f, 1.0f,	1.0f, 0.0f, // Bot - Right
	};


	GLuint indices[]
	{
		0, 1, 2,	// First triangle
		0, 3, 5,	// Second triangle
		3, 4, 5,	// Second triangle
		0, 2, 3,	// Second triangle
	};


	// Camera Variables
	glm::vec3 camPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 camLookDir = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 camUpDir = glm::vec3(0.0f, 1.0f, 0.0f);

	// Screen/Viewport size
	const unsigned int SCR_WIDTH = 800;
	const unsigned int SCR_HEIGHT = 800;

};

