#include "Mesh.h"

CMesh::CMesh(CCamera* _pCamera, GLuint* _pProgram, glm::vec3 _objPosition, glm::vec3 _objScale, float _rotationAngle)
{
	m_pCamera = _pCamera;
	m_pProgram = _pProgram;


	float fSize = 0.5;


	GLfloat vertices[]
	{
		// Position				// Colour			// Texture Coords
		-fSize, 0.0f, -fSize,	0.0f, 1.0f, 0.0f,	0.0f, 1.0f,
		-fSize, 0.0f,  fSize,	0.0f, 1.0f, 0.0f,	0.0f, 0.0f,
		 fSize, 0.0f,  fSize,	0.0f, 1.0f, 0.0f,	1.0f, 0.0f,
		 fSize, 0.0f, -fSize,	0.0f, 1.0f, 0.0f,	1.0f, 1.0f,
		
		-fSize, 0.0f, -fSize,	0.0f, 1.0f, 0.0f,	1.0f, 1.0f,
		 fSize, 0.0f, -fSize,	0.0f, 1.0f, 0.0f,	0.0f, 1.0f,

		 fSize, 0.0f, -fSize,	0.0f, 1.0f, 0.0f,	1.0f, 1.0f,
		 fSize, 0.0f,  fSize,	0.0f, 1.0f, 0.0f,	0.0f, 1.0f,

		 fSize, 0.0f,  fSize,	0.0f, 1.0f, 0.0f,	1.0f, 1.0f,
		-fSize, 0.0f,  fSize,	0.0f, 1.0f, 0.0f,	0.0f, 1.0f,

		-fSize, 0.0f,  fSize,	0.0f, 1.0f, 0.0f,	1.0f, 1.0f,
		-fSize, 0.0f, -fSize,	0.0f, 1.0f, 0.0f,	0.0f, 1.0f,
	
		 0.0f, fSize * 1.5f, 0.0f,0.0f, 1.0f, 0.0f,	0.5f, 0.0f,
	};


	GLuint indices[]
	{
		1, 0, 3,	// Base 1
		1, 3, 2,	// Base 2


		4, 12, 5,	// Side 1
		6, 12, 7,	// Side 2
		8, 12, 9,	// Side 3
		10, 12, 11,	// Side 4

		//3, 4, 2,	// Side 2
		//4, 4, 1,	// Side 3
		//1, 4, 0,	// Side 4
		//
		//1, 0, 3,
		//1, 3, 2,
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
	glm::mat4 scaleMatrix = scale(glm::mat4(), m_objScale * 10.0f);


	// Create model matrix to combine them
	m_matModel = translationMatrix * rotationZ * scaleMatrix;
}



void CMesh::Render()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	glUseProgram(*m_pProgram);

	// Binds the texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture01);
	glUniform1i(glGetUniformLocation(*m_pProgram, "tex0"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture02);
	glUniform1i(glGetUniformLocation(*m_pProgram, "tex1"), 1);

	glBindVertexArray(VAO);



	// Passes in all the matrixes
	GLuint modelLoc = glGetUniformLocation(*m_pProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(m_matModel));

	GLuint viewLoc = glGetUniformLocation(*m_pProgram, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(m_pCamera->GetView2D()));

	GLuint projLoc = glGetUniformLocation(*m_pProgram, "proj");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, value_ptr(m_pCamera->GetProj2D()));

	

	// Draws the triangle
	glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glUseProgram(0);
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


