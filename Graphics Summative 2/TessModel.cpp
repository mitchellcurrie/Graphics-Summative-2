#include "TessModel.h"

TessModel::TessModel(GLuint program, Camera* camera)
{
	this->m_program = program;
	this->m_camera = camera;

	m_fDistanceToCamera = 0.0f;

	GLfloat points[] = {
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 1.0f,  1.0f, 0.0f,
		-1.0f,  1.0f, 0.0f
	};

	glPatchParameteri(GL_PATCH_VERTICES, 4);

	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), &points, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

	glBindVertexArray(0);
}

void TessModel::render()
{
	glUseProgram(this->m_program);

	glm::mat4 model;
	model = glm::translate(model, position);
	glm::mat4 mvp = m_camera->GetProjectionMatrix() * m_camera->GetViewMatrix() * model;

	GLint mvLoc = glGetUniformLocation(m_program, "mvp");
	glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvp));

	GLuint distanceToCameraLoc = glGetUniformLocation(m_program, "distanceToCamera");
	glUniform1f(distanceToCameraLoc, m_fDistanceToCamera);

	glBindVertexArray(vao);
	glDrawArrays(GL_PATCHES, 0, 4);
	glBindVertexArray(0);
}

void TessModel::SetPosition(glm::vec3 _position)
{
	position = _position;
}

glm::vec3 TessModel::GetPostion()
{
	return position;
}

void TessModel::SetDistanceToCamera(glm::vec3 _tessModelPos, glm::vec3 _cameraPos)
{
	GLfloat distance = sqrt(((_tessModelPos.x - _cameraPos.x)*(_tessModelPos.x - _cameraPos.x)) +
							((_tessModelPos.y - _cameraPos.y)*(_tessModelPos.y - _cameraPos.y)) +
							((_tessModelPos.z - _cameraPos.z)*(_tessModelPos.z - _cameraPos.z)));

	m_fDistanceToCamera = static_cast<float>(distance);
	// std::cout << m_fDistanceToCamera;
}
