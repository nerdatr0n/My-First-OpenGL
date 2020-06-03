#include "Object.h"

CObject::CObject(CCamera* _pCamera, GLuint* _pProgram, GLuint* _pVAO, GLuint _pIndiceCount, GLuint* _pTexture)
{
	m_pCamera = _pCamera;
	m_pProgram = _pProgram;
	m_pVAO = _pVAO;
	m_pIndiceCount = _pIndiceCount;
	m_pTexture = _pTexture;


	m_vec3Location = glm::vec3(0.0f, 0.0f, 0.0f);
	m_vec3Scale = glm::vec3(1.0f, 1.0f, 1.0f);

	//m_vec3Scale *= 100;
	m_vec3RotationAxis = glm::vec3(0.0f, 0.0f, 1.0f);
	m_fRotationAngle = 0;

	Update();
}

void CObject::Render()
{

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	glUseProgram(*m_pProgram);



	// Binds the texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, *m_pTexture);
	glUniform1i(glGetUniformLocation(*m_pProgram, "tex0"), 0);

	// Passes in Location matrix
	GLuint modelLoc = glGetUniformLocation(*m_pProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(m_matModel));

	GLuint viewLoc = glGetUniformLocation(*m_pProgram, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(m_pCamera->GetView()));

	GLuint projLoc = glGetUniformLocation(*m_pProgram, "proj");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, value_ptr(m_pCamera->GetProj()));

	GLuint camPos = glGetUniformLocation(*m_pProgram, "camPos");
	glUniform3fv(camPos, 1, value_ptr(m_pCamera->GetPos()));

	glBindVertexArray(*m_pVAO);
	glDrawElements(GL_TRIANGLES, m_pIndiceCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}

void CObject::RenderReflections(GLuint* _pProgram, GLuint* _pTexture)
{

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	glUseProgram(*_pProgram);



	// Binds the texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, *m_pTexture);
	glUniform1i(glGetUniformLocation(*_pProgram, "tex0"), 0);


	glActiveTexture(GL_TEXTURE1);
	glUniform1i(glGetUniformLocation(*_pProgram, "skybox"), 1);
	glBindTexture(GL_TEXTURE_CUBE_MAP, *_pTexture);

	// Passes in Location matrix
	GLuint modelLoc = glGetUniformLocation(*_pProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(m_matModel));

	GLuint viewLoc = glGetUniformLocation(*_pProgram, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(m_pCamera->GetView()));

	GLuint projLoc = glGetUniformLocation(*_pProgram, "proj");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, value_ptr(m_pCamera->GetProj()));

	GLuint camPos = glGetUniformLocation(*_pProgram, "camPos");
	glUniform3fv(camPos, 1, value_ptr(m_pCamera->GetPos()));

	glBindVertexArray(*m_pVAO);
	glDrawElements(GL_TRIANGLES, m_pIndiceCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}

glm::vec3 CObject::GetLocation()
{
	return m_vec3Location;
}

void CObject::SetLocation(glm::vec3 _vec3Location)
{
	m_vec3Location = _vec3Location;
}


void CObject::Update()
{
	// Translation Matrix
	glm::mat4 translationMatrix = translate(glm::mat4(), m_vec3Location);

	// Rotation Matrix
	glm::mat4 rotationZ = rotate(glm::mat4(), glm::radians(m_fRotationAngle), m_vec3RotationAxis);

	// Scale Matrix
	glm::mat4 scaleMatrix = scale(glm::mat4(), m_vec3Scale);


	// Create model matrix to combine them
	m_matModel = translationMatrix * rotationZ * scaleMatrix;
}
