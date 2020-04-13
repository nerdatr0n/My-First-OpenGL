//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2020 Media Design School
//
// File Name   : camera.h
// Description : Header for camera class
// Author      : David Haverland
// Mail        : david.hav8466@mediadesign.school.nz
//


#pragma once


#include <glew.h>
#include <freeglut.h>
#include <SOIL.h>
#include <iostream>


#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#include "Utility.h"

class CCamera
{
public:
	CCamera(GLuint* _program);
	~CCamera();

	void Render();


private:

	const unsigned int SCR_WIDTH = Utils::SCR_WIDTH;
	const unsigned int SCR_HEIGHT = Utils::SCR_HEIGHT;

	glm::vec3 camPos;
	glm::vec3 camLookDir;
	glm::vec3 camUpDir;

	GLuint* m_pProgram;
};

