#include "Player.h"

CPlayer::CPlayer(CCamera* _pCamera,
	GLuint* _pProgram,
	GLuint* _pVAO,
	GLuint _pIndiceCount,
	GLuint* _pTexture)
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

	// Translation Matrix
	glm::mat4 translationMatrix = translate(glm::mat4(), m_vec3Location);

	// Rotation Matrix
	glm::mat4 rotationZ = rotate(glm::mat4(), glm::radians(m_fRotationAngle), m_vec3RotationAxis);

	// Scale Matrix
	glm::mat4 scaleMatrix = scale(glm::mat4(), m_vec3Scale);


	// Create model matrix to combine them
	m_matModel = translationMatrix * rotationZ * scaleMatrix;
}

CPlayer::~CPlayer()
{
}

void CPlayer::Update(CInput* _pInput, float _fDeltaTime)
{
	glm::vec2 vec2Input(0, 0);
	
	float fMovementSpeed = 10;
	
	if (_pInput->GetKey('A') == INPUT_DOWN or _pInput->GetKey('a') == INPUT_DOWN)
	{
		vec2Input.x--;
	}
	if (_pInput->GetKey('D') == INPUT_DOWN or _pInput->GetKey('d') == INPUT_DOWN)
	{
		vec2Input.x++;
	}
	
	if (_pInput->GetKey('W') == INPUT_DOWN or _pInput->GetKey('w') == INPUT_DOWN)
	{
		vec2Input.y--;
	}
	if (_pInput->GetKey('S') == INPUT_DOWN or _pInput->GetKey('s') == INPUT_DOWN)
	{
		vec2Input.y++;
	}

	
	vec2Input *= fMovementSpeed;
	
	//applys input
	m_vec3Location.x += vec2Input.x * _fDeltaTime;
	m_vec3Location.z += vec2Input.y * _fDeltaTime;




	//m_pPlayerObject->SetLocation(m_vec3Location);
	//m_pPlayerObject->Update();

		// Translation Matrix
	glm::mat4 translationMatrix = translate(glm::mat4(), m_vec3Location);

	// Rotation Matrix
	glm::mat4 rotationZ = rotate(glm::mat4(), glm::radians(m_fRotationAngle), m_vec3RotationAxis);

	// Scale Matrix
	glm::mat4 scaleMatrix = scale(glm::mat4(), m_vec3Scale);


	// Create model matrix to combine them
	m_matModel = translationMatrix * rotationZ * scaleMatrix;
}

void CPlayer::Render()
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
