#include "CStartButton.h"

CStartButton::CStartButton(CCamera* _pCamera, GLuint* _pProgram, FMOD::System* _audioSystem)
{

	Sprite = new CMesh2D(_pCamera,
		_pProgram,
		"Resource/Textures/StartButton.png",
		glm::vec2(156, 40),
		3,
		glm::vec3(512.0f, 256.0f, 0.0f));

	Button = new CButton(glm::vec2(512.0f, 256.0f), glm::vec2(156, 40));
}

CStartButton::~CStartButton()
{
	delete Sprite;
	delete Button;
}

void CStartButton::Update(float _deltaTime, CInput* _pInput)
{
	Sprite->Update();

	if (Button->CheckClick(_pInput))
	{
		std::cout << "Clicked" << std::endl;
		SwitchRoom(MAIN_LEVEL);
	}

	
	Button->UpdateFrame(_pInput);
}

void CStartButton::Render()
{
	Sprite->Render(Button->GetFrame());
}

Room CStartButton::GetSwitchRoom()
{
	if (m_bSwitchRoomFlag)
	{
		m_bSwitchRoomFlag = false;
		return m_Room;
	}
	return MAIN_MENU;
}

void CStartButton::SwitchRoom(Room _Room)
{
	m_bSwitchRoomFlag = true;
	m_Room = _Room;
}