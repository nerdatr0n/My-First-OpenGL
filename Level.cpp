#include "Level.h"


CLevel::CLevel(CCamera* _pCamera, FMOD::System* _audioSystem)
{
	m_pCamera = _pCamera;


	m_pBasicProgram = ShaderLoader::CreateProgram("Resource/Shaders/basic.vs",
		"Resource/Shaders/basic.fs");
	m_pPhongProgram = ShaderLoader::CreateProgram("Resource/Shaders/phong.vs",
		"Resource/Shaders/BlinnPhong.fs");
	m_pRimLightingProgram = ShaderLoader::CreateProgram("Resource/Shaders/phong.vs",
		"Resource/Shaders/RimLighting.fs");
	m_pCubeMapProgram = ShaderLoader::CreateProgram("Resource/Shaders/cubeMap.vs",
		"Resource/Shaders/cubeMap.fs");

	m_pObjSphere = new Sphere();



	CreateTexture(&m_pPlayerTexture, "Resource/Textures/Player.png");
	CreateTexture(&m_pEnemyTexture, "Resource/Textures/Enemy.png");
	m_pPlayer = new CPlayer(m_pCamera, &m_pPhongProgram, m_pObjSphere->GetVAO(), m_pObjSphere->GetIndiceCount(), &m_pPlayerTexture);
	m_pEnemy01 = new CEnemy(m_pCamera, &m_pRimLightingProgram, m_pObjSphere->GetVAO(), m_pObjSphere->GetIndiceCount(), &m_pEnemyTexture);
	m_pEnemy02 = new CEnemy(m_pCamera, &m_pRimLightingProgram, m_pObjSphere->GetVAO(), m_pObjSphere->GetIndiceCount(), &m_pEnemyTexture);

	m_pCubeMap = new CCubeMap(m_pCamera, &m_pCubeMapProgram);


	m_pFntPixel = new TextLabel("[SAMPLE TEXT]", "Resource/Fonts/m5x7.ttf", glm::vec2(12.0f, 12.0f), Color::offWhite);

	sndMusic = new CSound("Resource/Audio/sndMusic.mp3", _audioSystem, true);

	m_iScore = 0;
	m_iLives = 3;

	m_fDamaged = 0;
}

CLevel::~CLevel()
{
	delete m_pFntPixel;
	
	delete sndMusic;
	delete m_pHearts;
	delete m_pPlayer;

	delete m_pEnemy01;
	delete m_pEnemy02;

	delete m_pCubeMap;
}

void CLevel::Update(float _deltaTime, CInput* _pInput)
{
	m_pCubeMap->Update();
	m_pPlayer->Update(_pInput, _deltaTime);

	m_pEnemy01->Update(m_pPlayer->GetLocation(), _deltaTime);
	m_pEnemy02->Update(m_pPlayer->GetLocation(), _deltaTime);
}

void CLevel::Render()
{
	m_pCubeMap->Render();

	m_pPlayer->Render();
	m_pEnemy01->Render();
	m_pEnemy02->Render();



	m_pFntPixel->Render(glm::vec2(12.0f, 448.0f), "Score: " + std::to_string(m_iScore));
	m_pFntPixel->Render(glm::vec2(12.0f, 424.0f), "Lives: " + std::to_string(m_iLives));
}


void CLevel::Reset()
{

	//sndMusic->PlaySound();
	m_fDamaged = 0;

	m_pPlayer->Reset();
	//m_pEnemy01->Reset();
	//m_pEnemy02->Reset();

	m_iScore = 0;
	m_iLives = 3;
}


bool CLevel::WillSwitchRoom()
{
	return m_bSwitchRoomFlag;
}

int CLevel::GetHighScore()
{
	return m_iHighScore;
}

int CLevel::GetScore()
{
	return m_iScore;
}

Room CLevel::GetSwitchRoom()
{
	if (m_bSwitchRoomFlag)
	{
		m_bSwitchRoomFlag = false;
		return m_Room;
	}
	return MAIN_LEVEL;
}

void CLevel::SwitchRoom(Room _Room)
{
	m_bSwitchRoomFlag = true;
	m_Room = _Room;
}




void CLevel::CreateTexture(GLuint* _texture, const CHAR* _fileLocation)
{
	// Makes the texture
	glGenTextures(1, _texture);
	glBindTexture(GL_TEXTURE_2D, *_texture);

	// Makes variables to set the width and height to
	int width, height;
	unsigned char* image01 = SOIL_load_image(_fileLocation, &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image01);

	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image01);
	glBindTexture(GL_TEXTURE_2D, 0);
}