//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2016 Media Design School
//
// File Name   : Camera.cpp
// Description : The camera that handles the view and projection matrices
// Author	   : Juan Rodriguez
// Mail		   : juan.rod6618@mediadesignschool.com
//

#include "Camera.h"

Camera::Camera() {}

Camera::Camera(glm::vec3 _position, int _width, int _height) {

	position = _position;
	up = glm::vec3(0, 1, 0);
	forward = glm::vec3(0, 0, -1);

	width = _width;
	height = _height;

	speed = 1.5f;

	viewMatrix = GetViewMatrix();
	projectionMatrix = GetProjectionMatrix();

}

// Creates a camera with custom paramaters
// author		   : Juan Rodriguez
// param positions : the positions that the camera will face
// param _width    : the width of the camera
// param _height   : the height of the camera
// return		   : void
Camera::Camera(glm::vec3 positions[3], int _width, int _height) {

	position = positions[0];
	forward = positions[1];
	up = positions[2];

	width = _width;
	height = _height;

	viewMatrix = GetViewMatrix();
	projectionMatrix = GetProjectionMatrix();

}

// Create a view matrix with the lookAt function
// author : Juan Rodriguez
// return : mat4
glm::mat4 Camera::GetViewMatrix() const {

	return (glm::lookAt(position, position + forward, up));

}

// Create a projection matrix using the perspective function
// author : Juan Rodriguez
// return : mat4
glm::mat4 Camera::GetProjectionMatrix() const {

	return (glm::perspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 1000.0f));

}

glm::vec3 Camera::GetPosition() const {
	return (position);
}

glm::vec3 Camera::GetCameraForward()
{
	return forward;
}

void Camera::SetSpeed(float _speed) {

	this->speed = _speed;
}

void Camera::SetPosition(glm::vec3 newPosition) {

	position = newPosition;
}

void Camera::SetCameraForward(glm::vec3 _forward)
{
	forward = _forward;
}

void Camera::MoveForward() {
	
	if (position.z > -252.0f)
		//position -= glm::vec3(0.0f, 0.0f, 1.0f) * speed;
		position += normalize(forward) * speed;
}

void Camera::MoveBackward() {
	
	if (position.z < 252.0f)
		//position += glm::vec3(0.0f, 0.0f, 1.0f) * speed;
		position -= normalize(forward) * speed;
}

void Camera::MoveLeft() {
	
	if (position.x > -252.0f)
		//position -= glm::vec3(1.0f, 0.0f, 0.0f) * speed;
		position += normalize(glm::vec3(forward.z, forward.y, -forward.x)) * speed;
}

void Camera::MoveRight() {
	
	if (position.x < 252.0f)
		//position += glm::vec3(1.0f, 0.0f, 0.0f) * speed;
		position -= normalize(glm::vec3(forward.z, forward.y, -forward.x)) * speed;
}

void Camera::MoveUp() {
	
	//position += glm::vec3(0.0f, 1.0f, 0.0f) * speed;
}

void Camera::MoveDown() {
	//position -= glm::vec3(0.0f, 1.0f, 0.0f) * speed;
}

//void Camera::AdjustToTerrain(std::vector<VertexFormat> _terrainVertices)
//{
//	int z = static_cast<int>(position.z);
//	int x = static_cast<int>(position.x);
//	bool moveSet = false;
//	
//	for (auto itr = _terrainVertices.begin(); itr != _terrainVertices.end(); itr++)
//	{
//	/*	if ((abs(itr->pos.x - position.x) > 100.0f) && (abs(itr->pos.z - position.z) > 100.0f))
//		{
//			for (size_t i = 0; i < 50; i++)
//			{
//				itr++;
//			}
//		}*/
//
//		//if ((abs(itr->pos.x - position.x) > 20.0f) && (abs(itr->pos.z - position.z) > 20.0f))
//		//{
//		//	for (size_t i = 0; i < 10; i++)
//		//	{
//		//		itr++;
//		//	}
//		//}
//
//		if (!moveSet)
//		{
//			int move = (256 - z) * 256;
//			itr += move + x - 1;
//			moveSet = true;
//		}
//			
//			
//		if ((abs(itr->pos.x - position.x) < 2.0f) && (abs(itr->pos.z - position.z) < 2.0f))
//		{
//			position.y = itr->pos.y + 0.3f;
//			std::cout << "Match!";
//			return;
//		}
//
//
//		if (_terrainVertices.end() - itr < 4)
//		{
//			std::cout << "No!";
//			return;
//		}
//			
//		itr += 3;
//	}
//
//	std::cout << "No!";
//}

void Camera::AdjustToTerrainSimple(std::vector<VertexFormat> _terrainVertices)
{
	int z = static_cast<int>(position.z);
	int x = static_cast<int>(position.x);

	if (z <= 256 && z >= -256 && x <= 256 && x >= -256)
	{
		int move = ((256 - z) * 513) + x + 256;
		position.y = _terrainVertices.at(move).pos.y + 0.3f;
	}
}

//void Camera::AddTerrainVertices(std::vector<VertexFormat> _terrainVertices)
//{
//	//for (auto itr = _terrainVertices.begin(); itr != _terrainVertices.end(); itr++)
//	//{
//	//	if ((abs(itr->pos.x - position.x) < 10.0f) && (abs(itr->pos.z - position.z) < 10.0f))
//	//	{
//	//		closeTerrainVertices.push_back(*itr);
//	//	}
//	//}
//}
