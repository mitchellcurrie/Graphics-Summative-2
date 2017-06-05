#pragma once

#include "Utils.h"
#include "Light.h"

class Camera {
public:
	Camera();
	~Camera();
	Camera(glm::vec3 _position, int _width, int _height);
	Camera(glm::vec3 positions[3], int _width, int _height);
	glm::mat4 GetViewMatrix() const;
	glm::mat4 GetProjectionMatrix() const;
	glm::vec3 GetPosition() const;

	std::vector<VertexFormat> closeTerrainVertices;

	void SetSpeed(float _speed);
	void SetPosition(glm::vec3 position);
	void SetCameraForward(glm::vec3 _forward);

	void MoveForward();
	void MoveBackward();
	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();

	void AdjustToTerrain();
	void AddTerrainVertices(std::vector<VertexFormat> _terrainVertices);

private:
	int width, height;

	float speed;

	glm::vec3 position, up, forward;

	glm::mat4 viewMatrix, projectionMatrix;

};