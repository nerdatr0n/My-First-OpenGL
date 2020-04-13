#pragma once



#include <glew.h>
#include <freeglut.h>
#include <SOIL.h>
#include <iostream>
#include <fmod.hpp>

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"


#include "ShaderLoader.h"
#include "camera.h"
#include "TextLabel.h"


class CMesh
{
public:
	CMesh(CCamera* _pCamera, GLuint* _pProgram, 
		glm::vec3 _objPosition = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3 _objScale = glm::vec3(0.25f, 0.25f, 0.25f),
		float _rotationAngle = 0);

	~CMesh() {};

	void Update();
	void Render();
	
	 



private:

	void CreateTexture(GLuint* _texture, const CHAR* _fileLocation);

	// Render Data
	GLuint texture01;
	GLuint texture02;

	GLuint VAO;
	GLuint EBO;
	GLuint VBO;

	CCamera* m_pCamera;
	GLuint* m_pProgram;


	// Location Data
	glm::vec3 m_objPosition;
	glm::vec3 m_rotationAxisZ;
	float m_fRotationAngle;
	glm::vec3 m_objScale;
	glm::mat4 m_matModel;
};

