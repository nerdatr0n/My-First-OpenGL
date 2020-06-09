#pragma once

#include "Object.h"

class CEnemy : public CObject
{
public:
	CEnemy(CCamera* _pCamera,
		GLuint* _pProgram,
		GLuint* _pVAO,
		GLuint _pIndiceCount,
		GLuint* _pTexture,
		FMOD::System* _pAudioSystem);
	~CEnemy();

	void Update(glm::vec3 _vec3TargetLocation, float _fDeltaTime, glm::vec3 _vec3BulletLocation);

	void Reset();

	bool GetIncreaseScore();
	bool GetDamagedPlayer();

private:

	bool WillIncreaseScore = false;
	bool WillDamagedPlayer = false;

	float m_fMovementSpeed = 3;
};
