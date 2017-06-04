#pragma once

#include "Utils.h"
#include "Camera.h"

class TessModel
{
public:
	TessModel(GLuint program, Camera* camera);
	void render();
	void SetPosition(glm::vec3 _position);
	glm::vec3 GetPostion();
	void SetDistanceToCamera(glm::vec3 _tessModelPos, glm::vec3 _cameraPos);

private:
	GLuint vao, vbo, ebo, texture, texture1, texture2;
	glm::vec3 position;
	GLuint m_program;
	Camera* m_camera;
	float m_fDistanceToCamera;
};