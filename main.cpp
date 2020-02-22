

#include <glew.h>
#include <freeglut.h>
#include <iostream>

#include "ShaderLoader.h"


GLuint program;
GLfloat currentTime;

GLfloat vertices[]
{
	// Position				// Color
	-0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f, //Left
	 0.5f,  0.5f, 0.0f,		0.0f, 1.0f, 0.0f, //Left
	 0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f, //Left

	-0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f, //Left
	 0.5f,  0.5f, 0.0f,		0.0f, 1.0f, 0.0f, //Left
	-0.5f,  0.5f, 0.0f,		0.0f, 0.0f, 1.0f, //Left
};

GLuint VAO;
GLuint VBO;


void Render()
{
	glClear(GL_COLOR_BUFFER_BIT);

	// Render code will be written here
	glUseProgram(program);
	glBindVertexArray(VAO);

	currentTime = glutGet(GLUT_ELAPSED_TIME);
	currentTime = currentTime * 0.001f;

	GLint currentTimeLoc = glGetUniformLocation(program, "currentTime");
	glUniform1f(currentTimeLoc, currentTime);


	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	glUseProgram(0);


	glutSwapBuffers();
}

void Update()
{




	// Updates the game
	glutPostRedisplay();
}



int main(int argc, char** argv)
{

	// Setup and create at glut controlled window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(800, 800);
	glutCreateWindow("OpenGl First Window");


	// Sets up all gl function callbacks based on pc hardware
	if (glewInit() != GLEW_OK)
	{
		// If glew setup failed then application will not run graphics correctly
		std::cout << "glew Initalizzation Failed. Aborting application." << std::endl;
		system("pause");
		return 0;
	}


	// Sets the clear lolor when calling glClear()
	glClearColor(1.0, 0.0, 0.0, 1.0);

	program = ShaderLoader::CreateProgram("Resource/Shaders/basic.vs",
		"Resource/Shaders/basic.fs");

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);


	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);




	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);




	// Register callbacks
	glutDisplayFunc(Render);
	glutIdleFunc(Update);
	glutMainLoop();
	return 0;
}

