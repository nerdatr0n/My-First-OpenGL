#include "Mesh.h"

CMesh::CMesh(CCamera* _pCamera, GLuint* _pProgram, glm::vec3 _objPosition, glm::vec3 _objScale, float _rotationAngle)
{
	m_pCamera = _pCamera;
	m_pProgram = _pProgram;


	GLfloat vertices[]
	{
		// Position				// Color			// Texture Coords
		-4.0f,  5.0f, 0.0f,		1.0f, 0.0f, 0.0f,	 0.0f, 0.0f, // Top - Left
		-6.5f,  0.0f, 0.0f,		1.0f, 0.0f, 0.0f,	-0.2f, 0.5f, // Mid - Left
		-4.0f, -5.0f, 0.0f,		0.0f, 1.0f, 0.0f,	 0.0f, 1.0f, // Bot - Left
		 4.0f, -5.0f, 0.0f,		1.0f, 1.0f, 0.0f,	 1.0f, 1.0f, // Top - Right
		 6.5f,  0.0f, 0.0f,		1.0f, 1.0f, 0.0f,	 1.2f, 0.5f, // Mid - Right
		 4.0f,  5.0f, 0.0f,		0.0f, 0.0f, 1.0f,	 1.0f, 0.0f, // Bot - Right
	};


	GLuint indices[]
	{
		0, 1, 2,	// First triangle
		0, 3, 5,	// Second triangle
		3, 4, 5,	// Second triangle
		0, 2, 3,	// Second triangle
	};


	// Sets up location
	m_objPosition = _objPosition;

	m_objScale = _objScale;

	m_rotationAxisZ = glm::vec3(0.0f, 0.0f, 1.0f); // Axis to rotate on
	m_fRotationAngle = _rotationAngle; // Rotation amount


	
	

	// Creates the VBO, EBO and VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);



	// Makes the textures
	CreateTexture(&texture01, "Resource/Textures/Logo Small.png");
	CreateTexture(&texture02, "Resource/Textures/Merch.png");



	// Makes the points Point things
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);


}



void CMesh::Update()
{
	// Translation Matrix
	glm::mat4 translationMatrix = translate(glm::mat4(), m_objPosition);

	// Rotation Matrix
	glm::mat4 rotationZ = rotate(glm::mat4(), glm::radians(m_fRotationAngle), m_rotationAxisZ);

	// Scale Matrix
	glm::mat4 scaleMatrix = scale(glm::mat4(), m_objScale * 100.0f);


	// Create model matrix to combine them
	m_matModel = translationMatrix * rotationZ * scaleMatrix;
}



void CMesh::Render()
{
	glUseProgram(*m_pProgram);

	// Binds the texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture01);
	glUniform1i(glGetUniformLocation(*m_pProgram, "tex"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture02);
	glUniform1i(glGetUniformLocation(*m_pProgram, "tex1"), 1);

	glBindVertexArray(VAO);



	// Passes in Location matrix
	GLuint modelLoc = glGetUniformLocation(*m_pProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(m_matModel));



	

	// Draws the triangle
	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
}



//
// Creates Texture
// Argument: Texture Pointer, File Location
// Return: Void
//
void CMesh::CreateTexture(GLuint* _texture, const CHAR* _fileLocation)
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

