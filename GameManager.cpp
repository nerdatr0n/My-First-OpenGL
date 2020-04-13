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
// Calls the gamemanager render
// Argument: Void
// Return: Void
//
void RenderCallback()
{
	GlobalGameManager->Render();
}



//
// Calls the gamemanager Update
// Argument: Void
// Return: Void
//
void UpdateCallback()
{
	GlobalGameManager->Update();
}



//
// ???
// Argument: Void
// Return: Void
//
void KeyboardDownCallback(unsigned char key, int x, int y)
{
	GlobalGameManager->KeyboardDown(key, x, y);
}



//
// ???
// Argument: Void
// Return: Void
//
void KeyboardUpCallback(unsigned char key, int x, int y)
{
	GlobalGameManager->KeyboardUp(key, x, y);
}



//
// Constructer for GameMaker
// Argument: argc, argv
// Return: Void
//
GameManager::GameManager(int argc, char** argv)
{
	currentTime = 0;

	GlobalGameManager = this;



	// Camera Variables
	glm::vec3 camPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 camLookDir = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 camUpDir = glm::vec3(0.0f, 1.0f, 0.0f);

	// Screen/Viewport size
	const unsigned int SCR_WIDTH = Utils::SCR_WIDTH;
	const unsigned int SCR_HEIGHT = Utils::SCR_HEIGHT;




	// Setup and create at glut controlled window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(Utils::SCR_WIDTH, Utils::SCR_HEIGHT);
	glutCreateWindow("Hexagons: LightMode by [SAMPLE TEXT] Studios Ltd.");
	
	

	// Sets up all gl function callbacks based on pc hardware
	if (glewInit() != GLEW_OK)
	{
		// If glew setup failed then application will not run graphics correctly
		std::cout << "glew Initalizzation Failed. Aborting application." << std::endl;
		system("pause");
	}


	Text = new TextLabel("[SAMPLE TEXT]", "Resource/Fonts/AdventPro-Bold.ttf", glm::vec2(-350.0f, 300.0f));

	// Creates the program
	program = ShaderLoader::CreateProgram("Resource/Shaders/basic.vs",
		"Resource/Shaders/basic.fs");


	m_pCamera = new CCamera(&program);

	

	// Initalises the sound manager and sounds
	AudioInit();
	CreateSound(trackBackground, "Resource/Audio/Background.mp3");
	CreateSound(fxThump, "Resource/Audio/Thump.wav");

	FMOD_RESULT result;
	result = audioSystem->createSound(
		"Resource/Audio/Eric Taxxon - Nostalgia - 06 Warrior.mp3",
		FMOD_LOOP_NORMAL,
		0,
		&trackBackground);
	result = audioSystem->createSound(
		"Resource/Audio/Thump.wav",
		FMOD_DEFAULT,
		0,
		&fxThump);


	
	m_vecObjects.push_back(new CMesh(m_pCamera, &program, glm::vec3(300.0f, 0.0f, 0.0f)));
	m_vecObjects.push_back(new CMesh(m_pCamera, &program, glm::vec3(-300.0f, 0.0f, 0.0f)));

	// Wraps the texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Smoothes it
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);



	

	// Sets the clear color when calling glClear()
	glClearColor(1.0, 1.0, 1.0, 1.0);


	// Culls the not needed faces
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);



	

	result = audioSystem->playSound(trackBackground, 0, false, 0);

	if (result != FMOD_OK)
	{
		std::cout << "Big ol error" << std::endl;
	}


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
	fxThump->release();
	trackBackground->release();
	audioSystem->release();

	delete m_pCamera;

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



bool GameManager::CreateSound(FMOD::Sound* _sound, const CHAR* _fileLocation)
{
	FMOD_RESULT result;
	result = audioSystem->createSound(
		_fileLocation,
		FMOD_DEFAULT,
		0,
		&_sound);


	if (result != FMOD_OK)
	{
		return false;
	}
	return true;
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
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(program);
	// All the Camera things
	m_pCamera->Render();


	Text->Render();


	for (int i = 0; i < (int)m_vecObjects.size(); i++)
	{
		m_vecObjects[i]->Render();
	}

	

	// Makes and passes in the time uniform
	currentTime = static_cast<GLfloat>(glutGet(GLUT_ELAPSED_TIME));
	currentTime = currentTime * 0.001f;
	
	GLint currentTimeLoc = glGetUniformLocation(program, "currentTime");
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
	audioSystem->update();

	if (KeyState[' '] == INPUT_FIRST_DOWN)
	{
		std::cout << "Space" << std::endl;
		FMOD_RESULT result;

		result = audioSystem->playSound(fxThump, 0, false, 0);

		if (result != FMOD_OK)
		{
			std::cout << "Big ol error" << std::endl;
		}

	}

	for (int i = 0; i < (int)m_vecObjects.size(); i++)
	{
		m_vecObjects[i]->Update();
	}


	

	// Updates the game
	glutPostRedisplay();


	for (int i = 0; i < 255; i++)
	{
		if (KeyState[i] == INPUT_FIRST_DOWN)
		{
			KeyState[i] = INPUT_DOWN;
		}
		else if (KeyState[i] == INPUT_FIRST_UP)
		{
			KeyState[i] = INPUT_UP;
		}
	}

}




void GameManager::KeyboardInput()
{

}

void GameManager::KeyboardDown(unsigned char key, int x, int y)
{
	KeyState[key] = INPUT_FIRST_DOWN;
}

void GameManager::KeyboardUp(unsigned char key, int x, int y)
{
	KeyState[key] = INPUT_FIRST_UP;
}
