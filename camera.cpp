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

	m_pProgram = _program;

	// Camera Variables
	camPos = glm::vec3(0.0f, 0.0f, 3.0f);
	camLookDir = glm::vec3(0.0f, 0.0f, -1.0f);
	camUpDir = glm::vec3(0.0f, 1.0f, 0.0f);

}



//
// Makes the camera Matrix
// Argument: Void
// Return: Void
//
void CCamera::Render()
{
	glm::mat4 view = lookAt(camPos, camPos + camLookDir, camUpDir);

	GLuint viewLoc = glGetUniformLocation(*m_pProgram, "view");

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(view));


	glm::mat4 proj;
	float halfScreenWidth = (float)SCR_WIDTH * 0.5f;
	float halfScreenHeight = (float)SCR_HEIGHT * 0.5f;
	proj = glm::ortho(-halfScreenWidth, halfScreenWidth, -halfScreenHeight, halfScreenHeight, 0.1f, 100.0f);
	GLuint projLoc = glGetUniformLocation(*m_pProgram, "proj");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, value_ptr(proj));

}



//
// Calls the gamemanager Destructure
// Argument: Void
// Return: Void
//
CCamera::~CCamera()
{
}
