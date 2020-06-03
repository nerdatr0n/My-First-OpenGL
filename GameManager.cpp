//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2020 Media Design School
//
// File Name   : GameManager.cpp
// Description : Game Manager class
// Author      : David Haverland
// Mail        : david.hav8466@mediadesign.school.nz
//


#include "GameManager.h"





// So that the render thing works
GameManager* GlobalGameManager;



//
// Constructer for GameMaker
// Argument: argc, argv
// Return: Void
//
GameManager::GameManager(int argc, char** argv)
{
	currentTime = 0;

	GlobalGameManager = this;


	// Setup and create at glut controlled window
	glutInit(&argc, argv);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(Utils::SCR_WIDTH, Utils::SCR_HEIGHT);
	glutCreateWindow("Life in 3D: LightMode by [SAMPLE TEXT] Studios Ltd.");
	
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// Sets up all gl function callbacks based on pc hardware
	if (glewInit() != GLEW_OK)
	{
		// If glew setup failed then application will not run graphics correctly
		std::cout << "glew Initalizzation Failed. Aborting application." << std::endl;
		system("pause");
	}


	Text = new TextLabel("[SAMPLE TEXT]", "Resource/Fonts/AdventPro-Bold.ttf", glm::vec2(-500.0f, 300.0f));

	// Creates the program
	basicProgram = ShaderLoader::CreateProgram("Resource/Shaders/basic.vs",
		"Resource/Shaders/basic.fs");
	phongProgram = ShaderLoader::CreateProgram("Resource/Shaders/phong.vs",
		"Resource/Shaders/BlinnPhong.fs");
	cubeMapProgram = ShaderLoader::CreateProgram("Resource/Shaders/cubeMap.vs",
		"Resource/Shaders/cubeMap.fs");
	reflectionProgram = ShaderLoader::CreateProgram("Resource/Shaders/Reflection.vs",
		"Resource/Shaders/Reflection.fs");

	m_pCamera = new CCamera(&basicProgram);

	

	// Initalises the sound manager and sounds
	AudioInit();

	fxThump = new CSound("Resource/Audio/Thump.wav", audioSystem);
	
	m_pInputs = new CInput();
	
	m_vecObjects.push_back(new CMesh(m_pCamera, &basicProgram, glm::vec3(3.0f, 0.0f, 0.0f)));
	m_vecObjects.push_back(new CMesh(m_pCamera, &basicProgram, glm::vec3(-3.0f, 0.0f, 0.0f)));
	objSphere = new Sphere();

	

	m_pCubeMap = new CCubeMap(m_pCamera, &cubeMapProgram);
	model = new Model("Resource/Models/Tank/Tank.obj", m_pCamera);



	// Wraps the texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Smoothes it
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


	CreateTexture(&texture01, "Resource/Textures/Logo Small.png");
	
	GameObject = new CObject(m_pCamera, &phongProgram, objSphere->GetVAO(), objSphere->GetIndiceCount(), &texture01);
	m_pPlayer = new CPlayer(m_pCamera, &phongProgram, objSphere->GetVAO(), objSphere->GetIndiceCount(), &texture01);

	// Sets the clear color when calling glClear()
	//glClearColor(1.0, 1.0, 1.0, 1.0);
	glClearColor(0.0, 0.0, 0.0, 1.0);



	// Register callbacks
	glutDisplayFunc(RenderCallback);
	glutIdleFunc(UpdateCallback);
	//glCloseFunc(ShutDown);
	glutKeyboardFunc(KeyboardDownCallback);
	glutKeyboardUpFunc(KeyboardUpCallback);
	glutMainLoop();


}



//
// GameMaker Destructer
// Argument: Void
// Return: Void
//
GameManager::~GameManager()
{
	delete fxThump;
	fxThump = 0;


	audioSystem->release();

	delete objSphere;
	delete m_pCubeMap;
	delete m_pCamera;
	delete model;
	delete m_pPlayer;

	delete m_pInputs;

	for (int i = 0; i < (int)m_vecObjects.size(); i++)
	{
		delete m_vecObjects[i];
	}
}


bool GameManager::AudioInit()
{
	FMOD_RESULT result;
	result = FMOD::System_Create(&audioSystem);
	if (result != FMOD_OK)
	{
		return false;
	}


	result = audioSystem->init(100, FMOD_INIT_NORMAL | FMOD_INIT_3D_RIGHTHANDED, 0);
	if (result != FMOD_OK)
	{
		return false;
	}

	return true;
}



void GameManager::UpdateDeltaTime()
{
	m_fOldTime = m_fCurrentTime;
	m_fCurrentTime = static_cast<GLfloat>(glutGet(GLUT_ELAPSED_TIME)) / 1000;
	m_fDeltaTime = m_fCurrentTime - m_fOldTime;

}


//
// Creates Texture
// Argument: Texture Pointer, File Location
// Return: Void
//
void GameManager::CreateTexture(GLuint* _texture, const CHAR* _fileLocation)
{
	// Makes the texture
	glGenTextures(1, _texture);
	glBindTexture(GL_TEXTURE_2D, *_texture);

	// Makes variables to set the width and height to
	int width, height;
	unsigned char* image01 = SOIL_load_image(_fileLocation, &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image01);

	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image01);
	glBindTexture(GL_TEXTURE_2D, 0);
}



//
// Runs the Render
// Argument: Void
// Return: Void
//
void GameManager::Render()
{

	// Clears the Buffer - LEAVE AT TOP
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	
	m_pCubeMap->Render();
	

	glUseProgram(basicProgram);
	// All the Camera things
	m_pCamera->Render();


	Text->Render(glm::vec2(12.0f, 448.0f), "[SAMPLE TEXT]");

	m_pPlayer->Render();
	//GameObject->Render();
	//GameObject->RenderReflections(&reflectionProgram, m_pCubeMap->GetReflectionMap());
	
	model->Render();

	for (int i = 0; i < (int)m_vecObjects.size(); i++)
	{
		m_vecObjects[i]->Render();
	}

	// Makes and passes in the time uniform
	currentTime = static_cast<GLfloat>(glutGet(GLUT_ELAPSED_TIME));
	currentTime = currentTime * 0.001f;
	
	GLint currentTimeLoc = glGetUniformLocation(basicProgram, "currentTime");
	glUniform1f(currentTimeLoc, currentTime);



	

	glBindVertexArray(0);
	glUseProgram(0);



	// Swaps the buffers - LEAVE AT BOTTOM
	glutSwapBuffers();
}



//
// Runs the Update
// Argument: Void
// Return: Void
//
void GameManager::Update()
{
	UpdateDeltaTime();
	audioSystem->update();

	m_pCubeMap->Update();
	
	m_pPlayer->Update(m_pInputs, GetDeltatTime());
	//GameObject->Update();
	
	m_pCamera->Update(GetDeltatTime());

	

	if (KeyState[' '] == INPUT_FIRST_DOWN)
	{

		fxThump->PlaySound();

	}

	for (int i = 0; i < (int)m_vecObjects.size(); i++)
	{
		m_vecObjects[i]->Update();
	}
	

	

	// Updates the game
	glutPostRedisplay();



	m_pInputs->Update();



}




void GameManager::KeyboardDown(unsigned char key, int x, int y)
{
	m_pInputs->KeyboardDown(key, x, y);
}

void GameManager::KeyboardUp(unsigned char key, int x, int y)
{
	m_pInputs->KeyboardUp(key, x, y);
}

void GameManager::MouseClick(int button, int state, int x, int y)
{
	m_pInputs->MouseClick(button, state, x, y);
}

void GameManager::MousePassiveMove(int x, int y)
{
	m_pInputs->MousePassiveMove(x, y);
}

void GameManager::MouseMove(int x, int y)
{
	m_pInputs->MouseMove(x, y);
}


void RenderCallback()
{
	GlobalGameManager->Render();
}


void UpdateCallback()
{
	GlobalGameManager->Update();
}


void KeyboardDownCallback(unsigned char key, int x, int y)
{
	GlobalGameManager->KeyboardDown(key, x, y);
}


void KeyboardUpCallback(unsigned char key, int x, int y)
{
	GlobalGameManager->KeyboardUp(key, x, y);
}


void MouseClickCallback(int button, int state, int x, int y)
{
	GlobalGameManager->MouseClick(button, state, x, y);
}


void MousePassiveMoveCallback(int x, int y)
{
	GlobalGameManager->MousePassiveMove(x, y);
}


void MouseMoveCallback(int x, int y)
{
	GlobalGameManager->MouseMove(x, y);
}

