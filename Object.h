#pragma once


#include <glew.h>
#include <freeglut.h>
#include <SOIL.h>
#include <iostream>
#include <fmod.hpp>


#include "Mesh.h"
#include "Utility.h"
#include "Sound.h"
#include "Input.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

class CObject
{
public:
	CObject(CCamera* _pCamera,
		GLuint* _pProgram,
		GLuint* _pVAO,
		GLuint _pIndiceCount,
		GLuint* _pTexture,
		FMOD::System* _pAudioSystem);

	virtual void Render();
	virtual void Update();
	void RenderReflections(GLuint* _pProgram, GLuint* _pTexture);
	
	glm::vec3 GetLocation();
	void SetLocation(glm::vec3 _vec3Location);

	glm::mat4 GetModelMatrix()
	{
		return m_matModel;
	}

protected:
	// Location info
	glm::vec3 m_vec3Location;
	glm::vec3 m_vec3Scale;
	glm::vec3 m_vec3RotationAxis;
	float m_fRotationAngle;

	GLuint* m_pVAO;
	CCamera* m_pCamera;
	GLuint* m_pProgram;
	GLuint* m_pTexture;
	GLuint m_pIndiceCount;

	

	glm::mat4 m_matModel;
};

