//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2020 Media Design School
//
// File Name   : GameManager.cpp
// Description : Game Manager class
// Author      : David Haverland
// Mail        : david.hav8466@mediadesign.school.nz
//

#include <glew.h>
#include <freeglut.h>
#include <SOIL.h>
#include <iostream>
#include <fmod.hpp>

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#include "GameManager.h"
#include "ShaderLoader.h"
#include "camera.h"

using namespace glm;


GameManager* GlobalGameManager;


//
// Calls the gamemanager render
// Argument: Void
// Return: Void
//
void RenderCallback()
{
	GlobalGameManager->Render();
}



//
// Calls the gamemanager Update
// Argument: Void
// Return: Void
//
void UpdateCallback()
{
	GlobalGameManager->Update();
}



//
// Constructer for GameMaker
// Argument: argc, argv
// Return: Void
//
GameManager::GameManager(int argc, char** argv)
{

	// Creates 
	FMOD::System_Create(&audioSystem);


	currentTime = 0;

	GlobalGameManager = this;

	GLfloat vertices[]
	{
		// Position				// Color			// Texture Coords
		-4.0f,  5.0f, 0.0f,		1.0f, 0.0f, 0.0f,	 0.0f, 0.0f, // Top - Left
		-6.5f,  0.0f, 0.0f,		1.0f, 0.0f, 0.0f,	-0.2f, 0.5f, // Mid - Left
		-4.0f, -5.0f, 0.0f,		0.0f, 1.0f, 0.0f,	 0.0f, 1.0f, // Bot - Left
		 4.0f, -5.0f, 0.0f,		1.0f, 1.0f, 0.0f,	 1.0f, 1.0f, // Top - Right
		 6.5f,  0.0f, 0.0f,		1.0f, 1.0f, 0.0f,	 1.2f, 0.5f, // Mid - Right
		 4.0f,  5.0f, 0.0f,		0.0f, 0.0f, 1.0f,	 1.0f, 0.0f, // Bot - Right
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




	// Setup and create at glut controlled window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Hexagons: LightMode by [SAMPLE TEXT] Studios Ltd.");
	
	

	// Sets up all gl function callbacks based on pc hardware
	if (glewInit() != GLEW_OK)
	{
		// If glew setup failed then application will not run graphics correctly
		std::cout << "glew Initalizzation Failed. Aborting application." << std::endl;
		system("pause");
	
		// Didnt know what to replace this with so i just left it
		// return 0;
	}


	// Creates the program
	program = ShaderLoader::CreateProgram("Resource/Shaders/basic.vs",
		"Resource/Shaders/basic.fs");

	

	// Creates the VBO, EBO and VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);



	// Makes the textures
	CreateTexture(&texture01, "Resource/Textures/Logo Small.png");

	CreateTexture(&texture02, "Resource/Textures/Merch.png");


	// Wraps the texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Smoothes it
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);



	// Makes the points Point things
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	Camera  = new CCamera(&program);

	// Sets the clear color when calling glClear()
	glClearColor(1.0, 1.0, 1.0, 1.0);


	// Culls the not needed faces
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);


	// Register callbacks
	glutDisplayFunc(RenderCallback);
	glutIdleFunc(UpdateCallback);
	//glCloseFunc(ShutDown);
	glutMainLoop();


}



//
// GameMaker Destructer
// Argument: Void
// Return: Void
//
GameManager::~GameManager()
{

	delete Camera;
}



//
// Creates Texture
// Argument: Texture Pointer, File Location
// Return: Void
//
void GameManager::CreateTexture(GLuint* _texture, const CHAR* _fileLocation)
{
	// Makes the texture
	glGenTextures(1, _texture);
	glBindTexture(GL_TEXTURE_2D, *_texture);

	// Makes variables to set the width and height to
	int width, height;
	unsigned char* image01 = SOIL_load_image(_fileLocation, &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image01);

	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image01);
	glBindTexture(GL_TEXTURE_2D, 0);
}



//
// Runs the Render
// Argument: Void
// Return: Void
//
void GameManager::Render()
{
	glClear(GL_COLOR_BUFFER_BIT);

	// Render code will be written here
	glUseProgram(program);

	// Binds the texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture01);
	glUniform1i(glGetUniformLocation(program, "tex"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture02);
	glUniform1i(glGetUniformLocation(program, "tex1"), 1);

	glBindVertexArray(VAO);



	// Translation Matrix
	vec3 objPosition = vec3(170.0f, 0.0f, 0.0f);
	mat4 translationMatrix = translate(mat4(), objPosition);

	// Rotation Matrix
	vec3 rotationAxisZ = vec3(0.0f, 0.0f, 1.0f); // Axis to rotate on
	float rotationAngle = 0; // Rotation amount
	mat4 rotationZ = rotate(mat4(), radians(rotationAngle), rotationAxisZ);

	// Scale Matrix
	vec3 objScale = vec3(0.25f, 0.25f, 0.25f);
	mat4 scaleMatrix = scale(mat4(), objScale * 100.0f);

	// Create model matrix to combine them
	mat4 model = translationMatrix * rotationZ * scaleMatrix;
	GLuint modelLoc = glGetUniformLocation(program, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));


	Camera->Render();



	// Draws the triangle
	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

	// Translation Matrix
	objPosition = vec3(-170.0f, 0.0f, 0.0f);
	translationMatrix = translate(mat4(), objPosition);

	// Rotation Matrix
	rotationAxisZ = vec3(0.0f, 0.0f, 1.0f); // Axis to rotate on
	rotationAngle = 0; // Rotation amount
	rotationZ = rotate(mat4(), radians(rotationAngle), rotationAxisZ);

	// Scale Matrix
	objScale = vec3(0.25f, 0.25f, 0.25f);
	scaleMatrix = scale(mat4(), objScale * 100.0f);

	// Create model matrix to combine them
	model = translationMatrix * rotationZ * scaleMatrix;
	modelLoc = glGetUniformLocation(program, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));


	Camera->Render();

	// Draws the triangle
	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);


	// Makes and passes in the uniform
	currentTime = static_cast<GLfloat>(glutGet(GLUT_ELAPSED_TIME));
	currentTime = currentTime * 0.001f;

	GLint currentTimeLoc = glGetUniformLocation(program, "currentTime");
	glUniform1f(currentTimeLoc, currentTime);


	// Draws the triangle
	//glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);


	glBindVertexArray(0);
	glUseProgram(0);



	// Swaps the buffers
	glutSwapBuffers();
}



//
// Runs the Update
// Argument: Void
// Return: Void
//
void GameManager::Update()
{
	// Translation Matrix
	vec3 objPosition = vec3(0.5f, 0.5f, 0.0f);
	mat4 translationMatrix = translate(mat4(), objPosition);

	// Rotation Matrix
	vec3 rotationAxisZ = vec3(0.0f, 0.0f, 1.0f);
	float rotationAngle = 45;
	mat4 rotationZ = rotate(mat4(), radians(rotationAngle), rotationAxisZ);

	// Scale Matrix
	vec3 objScale = vec3(0.5f, 0.5f, 0.5f);
	mat4 scaleMatrix = scale(mat4(), objScale * 100.0f);

	// Create model matrix to combine them
	mat4 model = translationMatrix * rotationZ * scaleMatrix;
	GLuint modelLoc = glGetUniformLocation(program, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));



	// View Matrix
	mat4 view = lookAt(camPos, camPos + camLookDir, camUpDir);

	GLuint viewLoc = glGetUniformLocation(program, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(view));

	// Updates the game
	glutPostRedisplay();
}