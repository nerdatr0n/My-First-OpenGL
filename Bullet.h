#pragma once

#include "Object.h"

class CBullet : public CObject
{
public:
	CBullet(CCamera* _pCamera,
		GLuint* _pProgram,
		GLuint* _pVAO,
		GLuint _pIndiceCount,
		GLuint* _pTexture,
		FMOD::System* _pAudioSystem);

	~CBullet();

	void Update(float _fDeltaTime);
	void Shoot(glm::vec3 _vec3ShootDirection, glm::vec3 _vec3StartingPoint);

	glm::vec3 GetLocation()
	{
		return m_vec3Location;
	}

	
private:
	glm::vec3 m_vec3Velocity;

};

