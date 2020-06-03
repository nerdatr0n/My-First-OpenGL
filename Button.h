#pragma once

#include "Input.h"

class CButton
{
public:

	CButton(glm::ivec2 _ButtonPosition, glm::ivec2 _ButtonSize);
	~CButton();

	bool CheckClick(CInput* _pInput);

	int GetFrame();
	

	void UpdateFrame(CInput* _pInput);
private:

	int m_iFrame;

	bool m_bCanClick;
	

	bool IsMouseOver(CInput* _pInput);

	glm::ivec2 m_ButtonPosition;
	glm::ivec2 m_ButtonSize;
};

