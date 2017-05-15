#pragma once

#include "Camera.h"

class GeometryModel
{
public:

	GeometryModel(GLuint program, Camera* camera);
	void Render();
	void SetPosition(glm::vec3 position);

private:

	GLuint m_program;
	Camera* m_camera;
	GLuint vao;
	GLuint vbo;
	glm::vec3 m_Position;
};