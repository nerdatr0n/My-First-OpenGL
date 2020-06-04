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
	void Update(float DeltaTime);

	glm::mat4 GetVPMatrix();

	glm::mat4 GetView();
	glm::mat4 GetProj();
	glm::vec3 GetPos();

	glm::mat4 GetProj2D();
	glm::mat4 GetView2D();


private:

	float timeElapsed;

	const unsigned int SCR_WIDTH = Utils::SCR_WIDTH;
	const unsigned int SCR_HEIGHT = Utils::SCR_HEIGHT;

	glm::vec3 m_vec3CamPos;
	glm::vec3 m_vec3CamLookDir;
	glm::vec3 m_vec3CamUpDir;

	glm::vec3 m_vec3CamPos2D;
	glm::vec3 m_vec3CamLookDir2D;
	glm::vec3 m_vec3CamUpDir2D;

	//GLuint* m_pProgram;


	glm::mat4 m_mat4Proj;
	glm::mat4 m_mat4View;

	glm::mat4 m_mat4Proj2D;
	glm::mat4 m_mat4View2D;
};

