#include "CubeMap.h"





CCubeMap::CCubeMap(CCamera* _pCamera, GLuint* _pProgram)
{
	m_pCamera = _pCamera;
	m_pProgram = _pProgram;

	std::string textures[6]{ "right.jpg", "left.jpg", "top.jpg", "bottom.jpg", "back.jpg", "front.jpg" };

	int width, height;
	unsigned char* image;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);


	// Generates all the texturs
	for (GLuint i = 0; i < 6; i++)
	{
		std::string fullPathName = "Resource/CubeMaps/Lake/";
		fullPathName.append(textures[i]);
		image = SOIL_load_image(	fullPathName.c_str(),
									&width,
									&height,
									0,
									SOIL_LOAD_RGBA);

		glTexImage2D(	GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
						0,
						GL_RGBA,
						width,
						height,
						0,
						GL_RGBA,
						GL_UNSIGNED_BYTE,
						image);
		SOIL_free_image_data(image);
	}


	// Makes it look all smooth
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);


	float size = 0.5f;
	GLfloat vertices[]
	{
		// Front
		-size,	 size,	size,
		-size,	-size,	size,
		 size,	-size,	size,
		 size,	 size,	size,

		// Back
		-size,	 size, -size,	
		-size,	-size, -size,
		 size,	-size, -size,
		 size,	 size, -size,	

		// Left
		-size,	 size,	-size,	
		-size,	-size,	-size,
		-size,	-size,	 size,	
		-size,	 size,	 size,	

		// Right
		 size,	 size,	 size,
		 size,	-size,	 size,
		 size,	-size,	-size,
		 size,	 size,	-size,

		// Top
		-size,	 size,	-size,
		-size,	 size,	 size,
		 size,	 size,	 size,
		 size,	 size,	-size,

		// Bottom
		-size,	-size,	 size,
		-size,	-size,	-size,
		 size,	-size,	-size,
		 size,	-size,	 size,
	};

	GLuint indices[] =
	{
		0,	2,	1,
		0,	3,	2,

		7,	5,	6,
		7,	4,	5,

		8,	10,	9,
		8,	11,	10,

		12,	14,	13,
		12,	15,	14,

		16,	18,	17,
		16,	19,	18,

		20,	22,	21,
		20,	23,	22,
	};


	// Creates the VBO, EBO and VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Makes the points Point things
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
}

CCubeMap::~CCubeMap()
{

}


void CCubeMap::Update()
{
	glm::mat4 model = glm::scale(glm::mat4(), glm::vec3(200.0f, 200.0f, 200.0f));
	MVP = m_pCamera->GetVPMatrix() * model;
}


void CCubeMap::Render()
{
	glUseProgram(*m_pProgram);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

	GLuint CubeShaderUniform = glGetUniformLocation(*m_pProgram, "cubeSampler");
	glUniform1i(CubeShaderUniform, 0);


	GLuint MVPUniform = glGetUniformLocation(*m_pProgram, "MVP");
	glUniformMatrix4fv(MVPUniform, 1, GL_FALSE, glm::value_ptr(MVP));

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}

GLuint* CCubeMap::GetReflectionMap()
{
	return &texture;
}



