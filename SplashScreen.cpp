#include "SplashScreen.h"

CSplashScreen::CSplashScreen(CCamera* _pCamera, GLuint* _pProgram, FMOD::System* _audioSystem)
{
	sndSplashScreen = new CSound("Resource/Audio/sndSplashScreen.wav", _audioSystem);
	m_pSplashScreen = new CMesh2D(_pCamera,
		_pProgram,
		"Resource/Textures/SplashScreen.png",
		glm::vec2(1024, 512),
		1,
		glm::vec3(512.0f, 256.0f, 0.0f));

	sndMusic = new CSound("Resource/Audio/sndMusic.wav", _audioSystem, true);


	sndSplashScreen->PlaySound();
	m_fOpenTime = static_cast<GLfloat>(glutGet(GLUT_ELAPSED_TIME)) * 0.001f;
}

CSplashScreen::~CSplashScreen()
{
	delete sndSplashScreen;
	delete m_pSplashScreen;
}

void CSplashScreen::Update(float _deltaTime, CInput* _pInput)
{
	m_pSplashScreen->Update();

	float fCurrentTime = static_cast<GLfloat>(glutGet(GLUT_ELAPSED_TIME)) * 0.001f;

	if (fCurrentTime - m_fOpenTime > 10 or _pInput->GetKey(' ') == INPUT_FIRST_DOWN)
	{
		sndMusic->PlaySound();
		SwitchRoom(MAIN_MENU);
	}
}

void CSplashScreen::Render()
{
	m_pSplashScreen->Render();
}




Room CSplashScreen::GetSwitchRoom()
{
	if (m_bSwitchRoomFlag)
	{
		m_bSwitchRoomFlag = false;
		return m_Room;
	}
	return SPLASH_SCREEN;
}

void CSplashScreen::SwitchRoom(Room _Room)
{
	m_bSwitchRoomFlag = true;
	m_Room = _Room;
}
