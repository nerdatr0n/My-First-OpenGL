//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2020 Media Design School
//
// File Name   : main.cpp
// Description : Main file
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

#include "ShaderLoader.h"
#include "GameManager.h"
#include "camera.h"


using namespace glm;


//GLfloat currentTime;


//void ShutDown()
//{
//	gameManager->ShutDown();
//	delete gameManager;
//
//	gameManager = 0;
//}


int main(int argc, char** argv)
{




	GameManager gameManager(argc, argv);

	// Makes the c1onsole white
	system("color f0");




	// Sets the clear lolor when calling glClear()
	glClearColor(0.0, 0.0, 0.0, 1.0);



	// Culls the not needed faces
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);


	glutMainLoop();
	return 0;
}

