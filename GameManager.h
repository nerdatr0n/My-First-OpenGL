//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2020 Media Design School
//
// File Name   : GameManager.h
// Description : Header for Game Manager class
// Author      : David Haverland
// Mail        : david.hav8466@mediadesign.school.nz
//


#pragma once

#include <glew.h>
#include <freeglut.h>
#include <SOIL.h>
#include <iostream>
#include <fmod.hpp>
#include <vector>

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"


#include "ShaderLoader.h"
#include "camera.h"
#include "TextLabel.h"
#include "Mesh.h"
#include "Sphere.h"
#include "Sound.h"
#include "Object.h"
#include "CubeMap.h"
#include "Model.h"
#include "Player.h"
#include "Level.h"
#include "SplashScreen.h"
#include "MenuLevel.h"


void RenderCallback();
void UpdateCallback();


class GameManager
{
public:

	GameManager(int argc, char** argv);
	~GameManager();

	bool AudioInit();

	void CreateTexture(GLuint* _texture, const CHAR* _fileLocation);


	float GetDeltaTime() { return m_fDeltaTime; }


	// For callbacks
	void Render();
	void Update();
	void KeyboardDown(unsigned char key, int x, int y);
	void KeyboardUp(unsigned char key, int x, int y);
	void MouseClick(int button, int state, int x, int y);
	void MousePassiveMove(int x, int y);
	void MouseMove(int x, int y);

private:

	//Inputs 
	CInput* m_pInputs;

	void UpdateDeltaTime();

	float m_fOldTime;
	float m_fCurrentTime;
	float m_fDeltaTime;

	TextLabel* m_pText;

	GLuint m_iBasicProgram;


	CCamera* m_pCamera;

	// Audio
	FMOD::System* m_pAudioSystem;


	// Screen/Viewport size
	const unsigned int SCR_WIDTH = Utils::SCR_WIDTH;
	const unsigned int SCR_HEIGHT = Utils::SCR_HEIGHT;

	CLevel* m_pLevel;
	CSplashScreen* m_pSplashScreen;
	CMenuLevel* m_pMenuLevel;


	Room m_rCurrentRoom;
};



void RenderCallback();
void UpdateCallback();
void KeyboardDownCallback(unsigned char key, int x, int y);
void KeyboardUpCallback(unsigned char key, int x, int y);
void MouseClickCallback(int button, int state, int x, int y);
void MousePassiveMoveCallback(int x, int y);
void MouseMoveCallback(int x, int y);