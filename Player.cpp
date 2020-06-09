#include "Player.h"

CPlayer::CPlayer(CCamera* _pCamera,
	GLuint* _pProgram,
	GLuint* _pVAO,
	GLuint _pIndiceCount,
	GLuint* _pTexture,
	FMOD::System* _pAudioSystem) : CObject(_pCamera, _pProgram, _pVAO, _pIndiceCount, _pTexture, _pAudioSystem)
{
	m_vec3Scale *= 0.5;


	m_pShootSound = new CSound("Resource/Audio/sndJump.wav", _pAudioSystem);
}

CPlayer::~CPlayer()
{
	delete m_pShootSound;
}

void CPlayer::Update(CInput* _pInput, float _fDeltaTime, CBullet* _pBullet)
{
	glm::vec2 vec2Input(0, 0);
	
	float fMovementSpeed = 10;
	
	if (_pInput->GetKey('A') == INPUT_DOWN or _pInput->GetKey('a') == INPUT_DOWN)
	{
		vec2Input.x--;
	}
	if (_pInput->GetKey('D') == INPUT_DOWN or _pInput->GetKey('d') == INPUT_DOWN)
	{
		vec2Input.x++;
	}
	
	if (_pInput->GetKey('W') == INPUT_DOWN or _pInput->GetKey('w') == INPUT_DOWN)
	{
		vec2Input.y--;
	}
	if (_pInput->GetKey('S') == INPUT_DOWN or _pInput->GetKey('s') == INPUT_DOWN)
	{
		vec2Input.y++;
	}


	if (m_fBulletCooldown <= 0)
	{
		bool bDidShoot = ShootBullet(_pInput, _pBullet);
		if (bDidShoot)
		{
			m_pShootSound->PlaySound();
			m_fBulletCooldown = m_fBulletCooldownLength;
		}
	}
	m_fBulletCooldown -= _fDeltaTime;


	
	vec2Input *= fMovementSpeed;
	
	//applys input
	m_vec3Location.x += vec2Input.x * _fDeltaTime;
	m_vec3Location.z += vec2Input.y * _fDeltaTime;



	CObject::Update();
}



void CPlayer::Reset()
{
	m_vec3Location = glm::vec3(0.0f, 0.0f, 0.0f);
}

bool CPlayer::ShootBullet(CInput* _pInput, CBullet* _pBullet)
{
	glm::vec3 vec3ShootDirection(0, 0, 0);
	if (_pInput->GetKey('J') == INPUT_DOWN or _pInput->GetKey('j') == INPUT_DOWN)
	{
		vec3ShootDirection.x--;
	}
	if (_pInput->GetKey('L') == INPUT_DOWN or _pInput->GetKey('l') == INPUT_DOWN)
	{
		vec3ShootDirection.x++;
	}

	if (_pInput->GetKey('I') == INPUT_DOWN or _pInput->GetKey('i') == INPUT_DOWN)
	{
		vec3ShootDirection.z--;
	}
	if (_pInput->GetKey('K') == INPUT_DOWN or _pInput->GetKey('k') == INPUT_DOWN)
	{
		vec3ShootDirection.z++;
	}

	if (glm::length(vec3ShootDirection) > 0)
	{

		_pBullet->Shoot(vec3ShootDirection, m_vec3Location);
		return true;
	}
	

	return false;
}