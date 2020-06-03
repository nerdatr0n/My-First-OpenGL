#pragma once

#include "Object.h"

class CPlayer
{
public:
	CPlayer(CCamera* _pCamera,
		GLuint* _pProgram,
		GLuint* _pVAO,
		GLuint _pIndiceCount,
		GLuint* _pTexture);
	~CPlayer();

	void Render();
	void Update(CInput* _pInput, float _fDeltaTime);



private:
	GLuint* m_pVAO;
	CCamera* m_pCamera;
	GLuint* m_pProgram;
	GLuint* m_pTexture;
	GLuint m_pIndiceCount;

	// Location info
	glm::vec3 m_vec3Location;
	glm::vec3 m_vec3Scale;
	glm::vec3 m_vec3RotationAxis;
	float m_fRotationAngle;

	glm::mat4 m_matModel;
};

