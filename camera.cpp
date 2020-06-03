//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2020 Media Design School
//
// File Name   : camera.cpp
// Description : Camera class
// Author      : David Haverland
// Mail        : david.hav8466@mediadesign.school.nz
//




#include "camera.h"



//
// Constucture for Camera
// Argument: Program Pointer
// Return: Void
//
CCamera::CCamera(GLuint* _program)
{
	timeElapsed = 0;


	m_pProgram = _program;

	// Camera Variables
	camPos = glm::vec3(0.0f, 10.0f, 5.0f);
	camLookDir = glm::vec3(0.0f, 0.0f, -1.0f);
	camUpDir = glm::vec3(0.0f, 1.0f, 0.0f);
}

void CCamera::Update(float _DeltaTime)
{
	//timeElapsed += _DeltaTime;
	//GLfloat radius = 10.0f;
	//camPos.x = sin(timeElapsed) * radius;
	//camPos.y = 1.5f;
	//camPos.z = cos(timeElapsed) * radius;
	

	view = glm::lookAt(camPos, glm::vec3(0.0f, 0.0f, 0.0f), camUpDir);
	proj = glm::perspective(45.0f, (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
}

glm::mat4 CCamera::GetVPMatrix()
{

	return proj * view;
}

//
// Makes the camera Matrix
// Argument: Void
// Return: Void
//
void CCamera::Render()
{
	GLuint viewLoc = glGetUniformLocation(*m_pProgram, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(view));


	// Perspective Matrix/Camera
	GLuint projLoc = glGetUniformLocation(*m_pProgram, "proj");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, value_ptr(proj));
}

glm::mat4 CCamera::GetView()
{
	return view;
}

glm::mat4 CCamera::GetProj()
{
	return proj;
}

glm::vec3 CCamera::GetPos()
{
	return camPos;
}


//
// Calls the gamemanager Destructure
// Argument: Void
// Return: Void
//
CCamera::~CCamera()
{
}
