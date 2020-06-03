#pragma once

#include "Button.h"
#include "camera.h"
#include <fmod.hpp>
#include "Mesh.h"
#include "Mesh2D.h"

class CStartButton
{
public:
	CStartButton(CCamera* _pCamera, GLuint* _pProgram, FMOD::System* _audioSystem);
	~CStartButton();

	void Update(float _deltaTime, CInput* _pInput);
	void Render();

	Room GetSwitchRoom();

private:
	void SwitchRoom(Room _Room);

	Room m_Room;
	bool m_bSwitchRoomFlag;

	int m_iFrame;
	
	CMesh2D* Sprite;
	CButton* Button;

};

