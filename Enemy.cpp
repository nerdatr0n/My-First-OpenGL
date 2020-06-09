#include "Enemy.h"




CEnemy::CEnemy(CCamera* _pCamera,
	GLuint* _pProgram,
	GLuint* _pVAO,
	GLuint _pIndiceCount,
	GLuint* _pTexture,
	FMOD::System* _pAudioSystem) : CObject(_pCamera, _pProgram, _pVAO, _pIndiceCount, _pTexture, _pAudioSystem)
{
	
	m_vec3Location = glm::vec3(5.0f, 0.0f, -5.0f);
	m_vec3Scale = glm::vec3(1.0f, 1.0f, 1.0f);


	Reset();

	CObject::Update();
}

CEnemy::~CEnemy()
{
}

void CEnemy::Update(glm::vec3 _vec3TargetLocation, float _fDeltaTime, glm::vec3 _vec3BulletLocation)
{
	glm::vec3 Velocity;
	Velocity = _vec3TargetLocation - m_vec3Location;

	Velocity = glm::normalize(Velocity) * m_fMovementSpeed;

	//applys velocity
	m_vec3Location += Velocity * _fDeltaTime;

	// For when it hits the player
	if (glm::length(m_vec3Location - _vec3TargetLocation) < 2)
	{
		WillDamagedPlayer = true;
		Reset();
	}

	// For when a bullet hits it
	if (glm::length(m_vec3Location - _vec3BulletLocation) < 1)
	{
		WillIncreaseScore = true;
		Reset();
	}

	CObject::Update();
}


void CEnemy::Reset()
{
	float fPosition = (float)((rand() % 20) - 10);

	m_vec3Location = glm::vec3(fPosition, 0.0f, -10.0f);
}

bool CEnemy::GetIncreaseScore()
{
	if (WillIncreaseScore)
	{
		WillIncreaseScore = false;
		return true;
	}
	return false;
}

bool CEnemy::GetDamagedPlayer()
{
	if (WillDamagedPlayer)
	{
		WillDamagedPlayer = false;
		return true;
	}
	return false;
}



