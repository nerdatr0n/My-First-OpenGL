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
#include "Enemy.h"

class CLevel
{
public:
	//std::vector<CMesh*> m_vecObjects;
	CLevel(CCamera* _pCamera, FMOD::System* _audioSystem);
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
	CEnemy* m_pEnemy01;
	CEnemy* m_pEnemy02;

	CMesh2D* m_pHearts;

	GLuint* m_pProgram;

	CCamera* m_pCamera;

	int m_iHighScore = 0;


	GLuint m_pBasicProgram;
	GLuint m_pPhongProgram;
	GLuint m_pRimLightingProgram;
	GLuint m_pCubeMapProgram;


	CCubeMap* m_pCubeMap;

	Sphere* m_pObjSphere;

	GLuint m_pPlayerTexture;
	GLuint m_pEnemyTexture;

};

