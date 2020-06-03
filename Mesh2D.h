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


class CMesh2D
{
public:
	CMesh2D(CCamera* _pCamera,
		GLuint* _pProgram,
		const CHAR* _fileLocation,
		glm::vec2 _Size,
		unsigned int _iFrameCount = 1,
		glm::vec3 _objPosition = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3 _objScale = glm::vec3(1.0f, 1.0f, 1.0f),
		float _rotationAngle = 0.0f);

	~CMesh2D() {};

	void Update();
	void Render(int _iRenderFrame = 0);


	void SetLocation(glm::vec3 _location);
	void SetRotation(float _fRotation);
	void SetScale(glm::vec3 _Scale);



private:

	void CreateTexture(GLuint* _texture, const CHAR* _fileLocation);

	// Render Data
	GLuint texture;


	GLuint VAO;
	GLuint EBO;
	GLuint VBO;

	CCamera* m_pCamera;
	GLuint* m_pProgram;


	int m_iFrameCount;

	// Location Data
	glm::vec3 m_objPosition;
	glm::vec3 m_rotationAxisZ;
	float m_fRotationAngle;
	glm::vec3 m_objScale;
	glm::mat4 m_matModel;
};

