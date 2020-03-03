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

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#include "GameManager.h"
#include "ShaderLoader.h"

using namespace glm;


GameManager::GameManager(int argc, char** argv)
{
	// Setup and create at glut controlled window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(800, 800);
	glutCreateWindow("OpenGl First Window");


	// Sets up all gl function callbacks based on pc hardware
	if (glewInit() != GLEW_OK)
	{
		// If glew setup failed then application will not run graphics correctly
		std::cout << "glew Initalizzation Failed. Aborting application." << std::endl;
		system("pause");

		// Didnt know what to replace this with so i just left it
		// return 0;
	}


	// Sets the clear lolor when calling glClear()
	glClearColor(1.0, 0.0, 0.0, 1.0);



	// Culls the not needed faces
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);



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


	// Makes the texture
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// Makes variables to set the width and height to
	int width, height;
	unsigned char* image = SOIL_load_image("Resource/Textures/Logo Small.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);


	// Wraps the texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// smoothes it
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);



	// Makes the points Point things
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);


	// Register callbacks
	glutDisplayFunc(Render);
	glutIdleFunc(Update);
	//glCloseFunc(ShutDown);
	glutMainLoop();


}

GameManager::~GameManager()
{

}


void GameManager::Render()
{
	glClear(GL_COLOR_BUFFER_BIT);

	// Render code will be written here
	glUseProgram(program);


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


	// Orthographic Center Camera
	mat4 proj;
	float halfScreenWidth = (float)SCR_WIDTH * 0.5f;
	float halfScreenHeight = (float)SCR_HEIGHT * 0.5f;
	proj = ortho(-halfScreenWidth, halfScreenWidth, -halfScreenHeight, halfScreenHeight, 0.1f, 100.0f);
	GLuint projLoc = glGetUniformLocation(program, "proj");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, value_ptr(proj));



	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(program, "tex"), 0);

	glBindVertexArray(VAO);

	currentTime = glutGet(GLUT_ELAPSED_TIME);
	currentTime = currentTime * 0.001f;

	GLint currentTimeLoc = glGetUniformLocation(program, "currentTime");
	glUniform1f(currentTimeLoc, currentTime);


	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glUseProgram(0);




	glutSwapBuffers();
}




void GameManager::Update()
{


	// Updates the game
	glutPostRedisplay();
}