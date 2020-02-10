

#include <glew.h>
#include <freeglut.h>
#include <iostream>

#include "ShaderLoader.h"


GLuint program;


void Render()
{
	glClear(GL_COLOR_BUFFER_BIT);

	// Render code will be written here
	glUseProgram(program);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glUseProgram(0);

	glutSwapBuffers();
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



	// Register callbacks
	glutDisplayFunc(Render);
	glutMainLoop();
	return 0;
}

