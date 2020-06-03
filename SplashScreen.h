#pragma once

#include "Mesh2D.h"
#include "camera.h"
#include "Sound.h"
#include "Input.h"


class CSplashScreen
{
public:
	CSplashScreen(CCamera* _pCamera, GLuint* _pProgram, FMOD::System* _audioSystem);
	~CSplashScreen();

	void Update(float _deltaTime, CInput* _pInput);
	void Render();

	Room GetSwitchRoom();

private:
	void SwitchRoom(Room _Room);

	float m_fOpenTime;

	Room m_Room;
	bool m_bSwitchRoomFlag;

	CSound* sndMusic;
	CSound* sndSplashScreen;
	CMesh2D* m_pSplashScreen;
};

