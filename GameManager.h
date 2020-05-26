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

void RenderCallback();
void UpdateCallback();


class GameManager
{
public:

	GameManager(int argc, char** argv);
	~GameManager();

	bool AudioInit();

	void CreateTexture(GLuint* _texture, const CHAR* _fileLocation);



	void Render();
	void Update();
	void KeyboardInput();

	void KeyboardDown(unsigned char key, int x, int y);

	void KeyboardUp(unsigned char key, int x, int y);

	float GetDeltatTime() { return m_fDeltaTime; }

private:

	void UpdateDeltaTime();

	float m_fOldTime;
	float m_fCurrentTime;
	float m_fDeltaTime;

	InputState KeyState[255];
	TextLabel* Text;

	GLuint basicProgram;
	GLuint sphereProgram;
	GLuint phongProgram;
	GLuint cubeMapProgram;
	GLuint reflectionProgram;
	GLfloat currentTime;

	GLuint texture01;
	GLuint texture02;

	GLuint VAO;
	GLuint EBO;
	GLuint VBO;

	CCamera* m_pCamera;

	// Audio
	FMOD::System* audioSystem;
	CSound* fxThump;

	CObject* GameObject;

	CCubeMap* m_pCubeMap;

	// Screen/Viewport size
	const unsigned int SCR_WIDTH = Utils::SCR_WIDTH;
	const unsigned int SCR_HEIGHT = Utils::SCR_HEIGHT;


	// Objects
	std::vector<CMesh*> m_vecObjects;
	Sphere* objSphere;

};


