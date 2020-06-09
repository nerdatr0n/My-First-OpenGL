#include "Bullet.h"



CBullet::CBullet(CCamera* _pCamera,
	GLuint* _pProgram,
	GLuint* _pVAO,
	GLuint _pIndiceCount,
	GLuint* _pTexture,
	FMOD::System* _pAudioSystem) : CObject(_pCamera, _pProgram, _pVAO, _pIndiceCount, _pTexture, _pAudioSystem)
{
	m_vec3Scale *= 0.2;
	
	m_vec3Location = glm::vec3(999, 999, 999);
}


CBullet::~CBullet()
{
}

void CBullet::Update(float _fDeltaTime)
{

	m_vec3Location += m_vec3Velocity * _fDeltaTime;

	CObject::Update();
}

void CBullet::Shoot(glm::vec3 _vec3ShootDirection, glm::vec3 _vec3StartingPoint)
{
	m_vec3Velocity = glm::normalize(_vec3ShootDirection) * 50.0f;
	m_vec3Location = _vec3StartingPoint;
}


