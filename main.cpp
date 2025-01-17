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
#include <fmod.hpp>

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#include "ShaderLoader.h"
#include "GameManager.h"
#include "camera.h"





//
// Is the main
// Argument: atgc, argv pointer pointer
// Return: Void
//
int main(int argc, char** argv)
{
	// Makes the console white
	system("color f0");

	// Adds text to the console
	std::cout << std::endl << std::endl << "	This be mearly a console" << std::endl;
	std::cout << std::endl << "	Ya better not ask him any questions" << std::endl;


	GameManager gameManager(argc, argv);
	
	glutMainLoop();
	return 0;
}

