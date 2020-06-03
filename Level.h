#pragma once

//#include "GameManager.h"

#include "camera.h"
#include "Player.h"
#include "Mesh.h"
#include "Mesh2D.h"
//#include "Enemy.h"
#include "Input.h"
#include "Utility.h"
#include "Sphere.h"
#include "CubeMap.h"

class CLevel
{
public:
	//std::vector<CMesh*> m_vecObjects;
	CLevel(CCamera* _pCamera, GLuint* _pProgram, FMOD::System* _audioSystem);
	~CLevel();

	void Update(float _deltaTime, CInput* _pInput);
	void Render();

	void Reset();

	Room GetSwitchRoom();
	bool WillSwitchRoom();

	int GetHighScore();
	int GetScore();

private:
	void CreateTexture(GLuint* _texture, const CHAR* _fileLocation);
	void SwitchRoom(Room _Room);

	Room m_Room = MAIN_LEVEL;
	bool m_bSwitchRoomFlag = false;


	int m_iScore;
	int m_iLives;

	float m_fDamaged;

	CSound* sndMusic;

	TextLabel* m_pFntPixel;

	CPlayer* m_pPlayer;
	CMesh2D* m_pHearts;

	GLuint* m_pProgram;

	CCamera* m_pCamera;

	int m_iHighScore = 0;


	GLuint m_pBasicProgram;
	GLuint m_pPhongProgram;
	GLuint m_pCubeMapProgram;

	CCubeMap* m_pCubeMap;

	Sphere* m_pObjSphere;

	GLuint m_pPlayerTexture;

};

