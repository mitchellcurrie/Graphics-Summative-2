#include "GeometryModel.h"

GeometryModel::GeometryModel(GLuint program, Camera* camera)
{
	this->m_program = program;
	this->m_camera = camera;

	GLfloat points[] = {
		0.0f, 0.0f, 0.0f, 0.2f, 0.4f, 0.8f,  // passing in one point
	};

	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);

	glGenVertexArrays(1, &vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), &points, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));

	glBindVertexArray(0);
}

void GeometryModel::Render()
{
	glUseProgram(this->m_program);

	glm::mat4 model;
	model = glm::translate(model, m_Position);

	glm::mat4 mvp = m_camera->GetProjectionMatrix() * m_camera->GetViewMatrix() * model;

	GLint vpLoc = glGetUniformLocation(m_program, "mvp");
	glUniformMatrix4fv(vpLoc, 1, GL_FALSE, glm::value_ptr(mvp));

	glBindVertexArray(vao);
	glDrawArrays(GL_POINTS, 0, 1);
	glBindVertexArray(0);

}

void GeometryModel::SetPosition(glm::vec3 position)
{
	m_Position = position;
}
