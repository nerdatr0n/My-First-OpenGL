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


	//m_pProgram = _program;

	// Camera Variables
	m_vec3CamPos = glm::vec3(0.0f, 10.0f, 5.0f);
	m_vec3CamLookDir = glm::vec3(0.0f, 0.0f, -1.0f);
	m_vec3CamUpDir = glm::vec3(0.0f, 1.0f, 0.0f);


	m_vec3CamPos2D = glm::vec3((float)SCR_WIDTH / 2, (float)SCR_HEIGHT / 2, 3.0f);
	m_vec3CamLookDir2D = glm::vec3(0.0f, 0.0f, -1.0f);
	m_vec3CamUpDir2D = glm::vec3(0.0f, 1.0f, 0.0f);


}

void CCamera::Update(float _DeltaTime)
{
	//timeElapsed += _DeltaTime;
	//GLfloat radius = 10.0f;
	//camPos.x = sin(timeElapsed) * radius;
	//camPos.y = 1.5f;
	//camPos.z = cos(timeElapsed) * radius;
	

	m_mat4View = glm::lookAt(m_vec3CamPos, glm::vec3(0.0f, 0.0f, 0.0f), m_vec3CamUpDir);
	m_mat4Proj = glm::perspective(45.0f, (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);

	m_mat4View2D = lookAt(m_vec3CamPos2D, m_vec3CamPos2D + m_vec3CamLookDir2D, m_vec3CamUpDir2D);
	
	float halfScreenWidth = (float)SCR_WIDTH * 0.5f;
	float halfScreenHeight = (float)SCR_HEIGHT * 0.5f;
	m_mat4Proj2D = glm::ortho(-halfScreenWidth, halfScreenWidth, -halfScreenHeight, halfScreenHeight, 0.1f, 100.0f);
}

glm::mat4 CCamera::GetVPMatrix()
{
	return m_mat4Proj * m_mat4View;
}

//
// Makes the camera Matrix
// Argument: Void
// Return: Void
//
void CCamera::Render()
{
	//GLuint viewLoc = glGetUniformLocation(*m_pProgram, "view");
	//glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(view));
	//
	//
	//// Perspective Matrix/Camera
	//GLuint projLoc = glGetUniformLocation(*m_pProgram, "proj");
	//glUniformMatrix4fv(projLoc, 1, GL_FALSE, value_ptr(proj));
}

glm::mat4 CCamera::GetView()
{
	return m_mat4View;
}

glm::mat4 CCamera::GetProj()
{
	return m_mat4Proj;
}

glm::vec3 CCamera::GetPos()
{
	return m_vec3CamPos;
}

glm::mat4 CCamera::GetProj2D()
{
	return m_mat4Proj2D;
}

glm::mat4 CCamera::GetView2D()
{
	return m_mat4View2D;
}

//
// Calls the gamemanager Destructure
// Argument: Void
// Return: Void
//
CCamera::~CCamera()
{
}
