#pragma once

#include <glew.h>
#include <freeglut.h>

#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>

class Sphere
{
public:
	Sphere();
	~Sphere();

	void Render();
	GLuint* GetVAO();
	GLuint GetIndiceCount();

private:
	GLuint VAO;

	GLuint IndiceCount;
	int DrawType;
};

