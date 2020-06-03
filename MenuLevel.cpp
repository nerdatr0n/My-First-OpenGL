#include "MenuLevel.h"


CMenuLevel::CMenuLevel(CCamera* _pCamera, GLuint* _pProgram, FMOD::System* _audioSystem)
{
	m_pBackground = new CMesh2D(_pCamera,
		_pProgram,
		"Resource/Textures/MenuBackground.png",
		glm::vec2(1024, 512),
		2,
		glm::vec3(512.0f, 256.0f, 0.0f));

	StartButton = new CStartButton(_pCamera, _pProgram, _audioSystem);

	fntPixel = new TextLabel("[SAMPLE TEXT]", "Resource/Fonts/m5x7.ttf", glm::vec2(12.0f, 12.0f), Color::offBlack);

	m_iHighScore = 0;
	m_iPreviousScore = 0;
}

CMenuLevel::~CMenuLevel()
{
	delete m_pBackground;
	delete fntPixel;
	delete StartButton;
}


void CMenuLevel::Update(float _deltaTime, CInput* _pInput)
{
	m_pBackground->Update();
	StartButton->Update(_deltaTime, _pInput);


	Room SwitchToRoom = StartButton->GetSwitchRoom();
	if (SwitchToRoom != MAIN_MENU)
	{
		SwitchRoom(SwitchToRoom);
	}
}

void CMenuLevel::Render(int _Level, int _iHighScore, int m_iPreviousScore)
{
	int iBackgroundFrame = 0;
	if (_Level > 0 or _iHighScore != 0)
	{
		iBackgroundFrame = 1;
	}

	m_pBackground->Render(iBackgroundFrame);
	StartButton->Render();

	if (_Level > 0 or _iHighScore != 0)
	{
		fntPixel->Render(glm::vec2(12.0f, 476.0f), "High Score: " + std::to_string(_iHighScore));
		fntPixel->Render(glm::vec2(12.0f, 448.0f), "Score: " + std::to_string(m_iPreviousScore));
	}

	fntPixel->Render(glm::vec2(12.0f, 17.0f), GetLevelText(_Level));
}


Room CMenuLevel::GetSwitchRoom()
{
	if (m_bSwitchRoomFlag)
	{
		m_bSwitchRoomFlag = false;
		return m_Room;
	}
	return MAIN_MENU;
}

void CMenuLevel::SwitchRoom(Room _Room)
{
	m_bSwitchRoomFlag = true;
	m_Room = _Room;
}

std::string CMenuLevel::GetLevelText(int _iLevel)
{
	std::string FlavourText[18] =
	{
		"The light refers to light mode, nothing else.",
		"I swear this aint about racism, Just some good ol jumping.",
		"Its defiantly not about fighting white supremacy.",
		"Or about goomba stomping bad people.",
		"It could just be about getting knocked back.",
		"Or over analysis of art.",
		"I never told you to jump on their heads. racist.",
		"You think having a high score is something to brag about?",
		"Why do you still feel the need to come back.",
		"This whole game idea comes from discord's light mode.",
		"Maybe you thought this story would go somewhere?",
		"Don't know where you got that idea from.",
		"This is literally just an openGL project.",
		"There is nothing more to it.",
		"I just needed to justify an edgy name.",
		"And fooled you into thinking there was something more.",
		"Pranked",
		"Like I said at the start",
	};


	if (_iLevel > 17)
	{
		return "It just refers to the light mode.";
	}

	return FlavourText[_iLevel];
}
