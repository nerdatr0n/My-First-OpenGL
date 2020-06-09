#pragma once

#include "Object.h"
#include "Bullet.h"

class CPlayer : public CObject
{
public:
	CPlayer(CCamera* _pCamera,
		GLuint* _pProgram,
		GLuint* _pVAO,
		GLuint _pIndiceCount,
		GLuint* _pTexture,
		FMOD::System* _pAudioSystem);
	~CPlayer();

	void Update(CInput* _pInput, float _fDeltaTime, CBullet* _pBullet);

	void Reset();

	glm::vec3 GetLocation()
	{
		return m_vec3Location;
	}

	bool ShootBullet(CInput* _pInput, CBullet* _pBullet);


private:
	float m_fBulletCooldown = 0;
	float m_fBulletCooldownLength = 1;

	CSound* m_pShootSound;
};

