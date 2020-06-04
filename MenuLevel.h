#pragma once

#include "Mesh.h"
#include "camera.h"
#include "Sound.h"
#include "Input.h"
#include "CStartButton.h"

class CMenuLevel
{
public:
	CMenuLevel(CCamera* _pCamera, GLuint* _pProgram, FMOD::System* _audioSystem);
	~CMenuLevel();

	void Update(float _deltaTime, CInput* _pInput);
	void Render(int _Level, int _iHighScore, int m_iPreviousScore);

	Room GetSwitchRoom();

	

private:
	void SwitchRoom(Room _Room);

	

	Room m_Room;
	bool m_bSwitchRoomFlag;

	CMesh2D* m_pBackground;
	TextLabel* fntPixel;
	CStartButton* StartButton;

	int m_iHighScore;
	int m_iPreviousScore;
};

