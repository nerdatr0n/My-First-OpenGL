#pragma once

#include "Object.h"

class CEnemy// : public CObject
{
public:
	CEnemy(CCamera* _pCamera,
		GLuint* _pProgram,
		GLuint* _pVAO,
		GLuint _pIndiceCount,
		GLuint* _pTexture);
	~CEnemy();

	void Render();
	void Update(glm::vec3 TargetLocation, float _fDeltaTime);




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

	float m_fMovementSpeed = 1;
};
