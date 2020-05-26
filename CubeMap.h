#pragma once

#include <glew.h>
#include <freeglut.h>
#include <SOIL.h>
#include <iostream>
#include <fmod.hpp>

//#include <detail\type_mat.hpp>
//#include <gtc\matrix_transform.inl>

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#include "camera.h"
#include "ShaderLoader.h"

class CCubeMap
{
public:
	CCubeMap(CCamera* _pCamera, GLuint* _pProgram);
	~CCubeMap();

	void Update();
	void Render();
	GLuint* GetReflectionMap();

private:
	GLuint* m_pProgram;
	CCamera* m_pCamera;

	glm::mat4 MVP;

	GLuint VAO;
	GLuint EBO;
	GLuint VBO;

	GLuint texture;
};

