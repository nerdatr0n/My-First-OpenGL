
#include <glew.h>
#include <freeglut.h>
#include <SOIL.h>
#include <iostream>

#include "camera.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

using namespace glm;



CCamera::CCamera(GLuint* _program)
{

	m_pProgram = _program;

	// Camera Variables
	camPos = glm::vec3(0.0f, 0.0f, 3.0f);
	camLookDir = glm::vec3(0.0f, 0.0f, -1.0f);
	camUpDir = glm::vec3(0.0f, 1.0f, 0.0f);


	// Screen/Viewport size
	//const unsigned int SCR_WIDTH = 800;
	//const unsigned int SCR_HEIGHT = 800;

	// View Matrix

	


	// Orthographic Center Camera
	//mat4 proj;
	//float halfScreenWidth = (float)SCR_WIDTH * 0.5f;
	//float halfScreenHeight = (float)SCR_HEIGHT * 0.5f;
	//proj = ortho(-halfScreenWidth, halfScreenWidth, -halfScreenHeight, halfScreenHeight, 0.1f, 100.0f);
	//GLuint projLoc = glGetUniformLocation(*m_pProgram, "proj");
	//glUniformMatrix4fv(projLoc, 1, GL_FALSE, value_ptr(proj));
}

void CCamera::Render()
{
	mat4 view = lookAt(camPos, camPos + camLookDir, camUpDir);

	GLuint viewLoc = glGetUniformLocation(*m_pProgram, "view");

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(view));


	mat4 proj;
	float halfScreenWidth = (float)SCR_WIDTH * 0.5f;
	float halfScreenHeight = (float)SCR_HEIGHT * 0.5f;
	proj = ortho(-halfScreenWidth, halfScreenWidth, -halfScreenHeight, halfScreenHeight, 0.1f, 100.0f);
	GLuint projLoc = glGetUniformLocation(*m_pProgram, "proj");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, value_ptr(proj));

}

CCamera::~CCamera()
{
}
