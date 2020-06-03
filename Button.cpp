#include "Button.h"
#include <iostream>

CButton::CButton(glm::ivec2 _ButtonPosition, glm::ivec2 _ButtonSize)
{
	m_ButtonPosition = _ButtonPosition;
	m_ButtonSize = _ButtonSize;

	m_bCanClick = false;
}

CButton::~CButton()
{
}

bool CButton::CheckClick(CInput* _pInput)
{
	// Checks if the player has pressed the mouse buttion down
	if (_pInput->GetMouse(0) == INPUT_FIRST_DOWN and IsMouseOver(_pInput))
	{
		m_bCanClick = true;
	}




	// Checks if the player has released the mouse buttion correctly
	if (_pInput->GetMouse(0) == INPUT_FIRST_UP or _pInput->GetMouse(0) == INPUT_UP)
	{
		if (IsMouseOver(_pInput) and m_bCanClick)
		{
			// Will initate the click action
			m_bCanClick = false;
			return true;
		}
		else
		{
			m_bCanClick = false;
		}
	}

	return false;
}

int CButton::GetFrame()
{
	return m_iFrame;
}

void CButton::UpdateFrame(CInput* _pInput)
{
	// Checks for mouse over
	if (IsMouseOver(_pInput))
	{

		// Checks if the buttion should be depressed
		if (m_bCanClick)
		{
			m_iFrame = 2;
		}

		else
		{
			m_iFrame = 1;
		}
	}

	// for When mouse is not over
	else
	{
		m_iFrame = 0;
	}
}

bool CButton::IsMouseOver(CInput* _pInput)
{
	glm::ivec2 MousePosition = _pInput->GetMousePosition();

	if (abs(MousePosition.x - m_ButtonPosition.x) < m_ButtonSize.x and abs(MousePosition.y - m_ButtonPosition.y) < m_ButtonSize.y)
	{
		return true;
	}

	return false;
}
