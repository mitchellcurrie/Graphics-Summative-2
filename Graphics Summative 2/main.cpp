//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2016 Media Design School
//
// File Name   : main.cpp
// Description : main implementation file; creates the window, checks for user input, loads images
// Author	   : Juan Rodriguez
// Mail		   : juan.rod6618@mediadesignschool.com
//

#include <iostream>

#include "Utils.h"
#include "Camera.h"
#include "GameModel.h"
#include "Cubemap.h"
#include "model.h"
#include "terrain.h"
#include "GeometryModel.h"
#include "TessModel.h"
#include "frameBuffer.h"
#include <string>
#include <ctime>

// PCG
#include <cmath>
#include "RAW.h"
#include "PerlinNoise.h"

// #define SEED 1

const std::wstring FILENAME = L"assets/heightmap/PCG_MAP.raw";

#define DOWN 1
#define UP 0

#define MOUSE_LEFT 0
#define MOUSE_MIDDLE 1
#define MOUSE_RIGHT 2

using std::cout;
using glm::vec3;

// Classes
Utils* ut;
ShaderLoader shaderLoader;
Camera* camera;
Light* light;
GameModel* Sphere;
GameModel* Sphere2;
GameModel* Sphere3;
Cubemap* skybox;
GameModel* Cube;
GameModel* Mirror;
GameModel* ReflectedCube;
GameModel* LightSphere;
Terrain* terrain;
GeometryModel* geomModel;
TessModel* tessModel;
FrameBuffer* frameBuffer;

// Bullets
GameModel* bullet;
std::vector<GameModel*> bulletVector;
float bulletFireRate = 0.3f;
float TimeNew = 0.0f;
float TimeOld = 0.0f;
float bulletTimer = 0.0f;

// Mouse
unsigned char mouseState[3];

GLfloat yaw = -90.0f;
GLfloat pitch = 0.0f;
GLfloat lastX = Utils::WIDTH / 2.0;
GLfloat lastY = Utils::HEIGHT / 2.0;
bool firstMouse = true;

// Move everything
float fMoveY = 87.0f;
int iMoveY = static_cast<int>(fMoveY);

float fMoveX = 13.0f;
int iMoveX = static_cast<int>(fMoveX);

// Custom models
Model *Castle, *Nanosuit;

unsigned char KeyCode[255];
bool WireDraw = false;
bool Culling = true;
bool AntiA = true;
bool Greyscale = false;

void Init();
void Render();
void Update();
void KeyDown(unsigned char key, int x, int y);
void KeyUp(unsigned char key, int x, int y);

void mousePassiveMove(int x, int y);
void mouse(int button, int button_state, int x, int y);

void GeneratePerlinNoiseMap(unsigned int width, unsigned int height, string fileName);

int main(int argc, char **argv) {

	// init glut
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
//	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(GLUT_WINDOW_WIDTH / 2, GLUT_WINDOW_HEIGHT / 2);
	glutInitWindowSize(ut->WIDTH, ut->HEIGHT);
	glutSetOption(GLUT_MULTISAMPLE, 8);
	glEnable(GL_MULTISAMPLE);
	glutCreateWindow("Advanced Graphics - Summative 1 - Juan Rodriguez and Mitchell Currie");


	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);               // Set background color to black and opaque
	glClearDepth(1.0f);                                 // Set background depth to farthest
	glEnable(GL_DEPTH_TEST);                            // Enable depth testing for z-culling
	glDepthFunc(GL_LEQUAL);                             // Set the type of depth-test
	glShadeModel(GL_SMOOTH);                            // Enable smooth shading
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections

	// To test whether backface culling is working, wire draw mode
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glewInit();
	Init();

	glutDisplayFunc(Render);
	glutKeyboardFunc(KeyDown);
	glutKeyboardUpFunc(KeyUp);
	glutIdleFunc(Update);

	glutMouseFunc(mouse);
	glutPassiveMotionFunc(mousePassiveMove);

	glutMainLoop();

	return (EXIT_SUCCESS);

}

void Init()
{
	// -- Object creation
	camera = new Camera(vec3(0 + iMoveX, 4 + iMoveY, 8), ut->WIDTH, ut->HEIGHT);
	camera->SetSpeed(0.5f);  // was 0.03
	light = new Light(vec3(0 + iMoveX, 5 + iMoveY, 0), vec3(0.5f, 0.5f, 0.5f));
	light->SetSpeed(0.04f);

	// Sphere
	GLuint sphereProgram = shaderLoader.CreateProgram("assets/shaders/specular.vs", "assets/shaders/specular.fs");
	Sphere = new GameModel(ModelType::kSphere, camera, "assets/textures/books.jpg", light, 0.65f, 4.3f);
	Sphere->SetProgram(sphereProgram);
	Sphere->SetPosition(vec3(-6.0f + fMoveX, 4.5f + fMoveY, 0));
	Sphere->SetSpeed(0.005f);

	// Sphere 2
	GLuint sphere2Program = shaderLoader.CreateProgram("assets/shaders/specular.vs", "assets/shaders/specular.fs");
	Sphere2 = new GameModel(ModelType::kSphere, camera, "assets/textures/books.jpg", light, 0.65f, 4.3f);
	Sphere2->SetProgram(sphere2Program);
	Sphere2->SetPosition(vec3(-6.0f + fMoveX, 4.5f + fMoveY, -3.0f));
	Sphere2->SetSpeed(0.005f);

	// Sphere 3
	GLuint sphere3Program = shaderLoader.CreateProgram("assets/shaders/specular.vs", "assets/shaders/specular.fs");
	Sphere3 = new GameModel(ModelType::kSphere, camera, "assets/textures/books.jpg", light, 0.65f, 4.3f);
	Sphere3->SetProgram(sphere3Program);
	Sphere3->SetPosition(vec3(-6.0f + fMoveX, 4.5f + fMoveY, -6.0f));
	Sphere3->SetSpeed(0.005f);

	// Skybox
	GLuint cubemapProgram = shaderLoader.CreateProgram("assets/shaders/skybox.vs", "assets/shaders/skybox.fs");
	skybox = new Cubemap(cubemapProgram, camera);

	//// Cube
	//GLuint cubeProgram = shaderLoader.CreateProgram("assets/shaders/specular.vs", "assets/shaders/specular.fs");
	//Cube = new GameModel(ModelType::kCube, camera, "assets/textures/triangle.jpg", light, 0.65f, 4.3f);
	//Cube->SetProgram(cubeProgram);
	//Cube->SetPosition(vec3(6, -0.5f, 0));
	//Cube->SetSpeed(0.005f);
	//Cube->SetScale(vec3(0.7f, 0.7f, 0.7f));

	//// Reflected Cube
	//GLuint refCubeProgram = shaderLoader.CreateProgram("assets/shaders/specular.vs", "assets/shaders/specular.fs");
	//ReflectedCube = new GameModel(ModelType::kCube, camera, "assets/textures/triangle.jpg", light, 0.2f, 0.5f);
	//ReflectedCube->SetProgram(refCubeProgram);
	//ReflectedCube->SetPosition(vec3(6, -1.9f, 0));
	//ReflectedCube->SetSpeed(0.005f);
	//ReflectedCube->SetScale(vec3(0.7f, 0.7f, 0.7f));

	//// Mirror
	//GLuint mirrorProgram = shaderLoader.CreateProgram("assets/shaders/specular.vs", "assets/shaders/specular.fs");
	//Mirror = new GameModel(ModelType::kQuad, camera, "assets/textures/black.jpg", light, 0.65f, 4.3f);
	//Mirror->SetProgram(mirrorProgram);
	//Mirror->SetPosition(vec3(6, -1.2f, 0));
	////Mirror->SetSpeed(0.0f);
	//Mirror->Rotate(vec3(90.0f, 0.0f, 0.0f));
	//Mirror->SetScale(vec3(2.5f, 2.5f, 2.5f));

	// Light Sphere
	GLuint lightSphereProgram = shaderLoader.CreateProgram("assets/shaders/specular.vs", "assets/shaders/specular.fs");
	LightSphere = new GameModel(ModelType::kSphere, camera, "assets/textures/white.jpg", light, 3.0f, 4.3f);
	LightSphere->SetProgram(lightSphereProgram);
	LightSphere->SetPosition(light->GetPosition());
	LightSphere->SetSpeed(0.005f);
	LightSphere->SetScale(vec3(0.2f, 0.2f, 0.2f));

	//// Model
	//GLuint modelProgram = shaderLoader.CreateProgram("assets/shaders/model.vs", "assets/shaders/model.fs");
	//Nanosuit = new Model("assets/models/Nanosuit/nanosuit.obj", camera, modelProgram);
	//Nanosuit->SetPosition(vec3(-0.05f + fMoveX, 1.6f + fMoveY, 2.75));
	//Nanosuit->SetScale(vec3(0.04f));

	//Castle = new Model("assets/models/Castle/Castle OBJ.obj", camera, modelProgram);
	//Castle->SetPosition(vec3(0 + fMoveX, 1.6f + fMoveY, 0));
	//Castle->SetScale(vec3(0.1f));

	// Terrain
	string FILENAME_string = string(FILENAME.begin(), FILENAME.end());
	srand((unsigned int)time(NULL));
	GeneratePerlinNoiseMap(513, 513, FILENAME_string);

	GLuint terrainProgram = shaderLoader.CreateProgram("assets/shaders/heightmap.vs", "assets/shaders/heightmap.fs");
	terrain = new Terrain(FILENAME,
		"assets/heightmap/sand.jpg",
		"assets/heightmap/grass.jpg",
		"assets/heightmap/rock.jpg",
		terrainProgram,
		camera,
		light);

	// Geometry Model
	GLuint geomProgram = shaderLoader.CreateProgram("assets/shaders/geometry.vs", "assets/shaders/geometry.fs",
		"assets/shaders/geometry.gs");
	geomModel = new GeometryModel(geomProgram, camera);
	geomModel->SetPosition(glm::vec3(5.0f + fMoveX, 19.0f + fMoveY, -20.0f));

	// Tesselation Model
	GLuint tessProgram = shaderLoader.CreateProgram("assets/shaders/TessModel.vs", "assets/shaders/TessModel.fs",
		"assets/shaders/TessModel.tcs", "assets/shaders/TessModel.tes");
	tessModel = new TessModel(tessProgram, camera);
	tessModel->SetPosition(glm::vec3(0.0f + fMoveX, 3.0f + fMoveY, 0.0f));

	// Bullets
	GLuint bulletProgram = shaderLoader.CreateProgram("assets/shaders/specular.vs", "assets/shaders/specular.fs");

	for (size_t x = 0; x < 20; x++)
	{
		bullet = new GameModel(ModelType::kCube, camera, "assets/textures/triangle.jpg", light, 0.65f, 4.3f);
		bullet->SetProgram(bulletProgram);
		bullet->SetPosition(vec3(0, -30, 0));
		bullet->SetSpeed(5.0f);
		bullet->SetScale(vec3(0.1f, 0.1f, 0.1f));
		bulletVector.push_back(bullet);
	}

	TimeOld = static_cast<float>((GLfloat)glutGet(GLUT_ELAPSED_TIME));

	// Frame buffer
	GLuint FBProgram = shaderLoader.CreateProgram("assets/shaders/frameBuffer.vs",
		"assets/shaders/frameBuffer.fs");
	frameBuffer = new FrameBuffer(FBProgram);	

	camera->AdjustToTerrainSimple(terrain->GetVertices());

	Sphere->SetPosition(camera->GetPosition() + vec3(4.0f, 5.0f, -8.0f));
	Sphere2->SetPosition(camera->GetPosition() + vec3(4.0f, 5.0f, -11.0f));
	Sphere3->SetPosition(camera->GetPosition() + vec3(4.0f, 5.0f, -14.0f));
	light->SetPosition(camera->GetPosition() + vec3(7.0f, 4.0f, -5.0f));
	geomModel->SetPosition(camera->GetPosition() + vec3(-10.0f, 25.0f, -5.0f));
	tessModel->SetPosition(camera->GetPosition() + vec3(0.0f, 6.0f, -5.0f));
}

void Render() {

	if (!WireDraw) { frameBuffer->Setup(); }

	glClearColor(0.529f, 0.8078f, 0.98f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	//skybox->Render();

	// Backface culling for sphere
	//if (Culling)
	//	glEnable(GL_CULL_FACE);

	//glFrontFace(GL_CCW);
	//glCullFace(GL_FRONT);
	//Sphere->Render();
	//glDisable(GL_CULL_FACE);

//	Castle->Draw();
//	Nanosuit->Draw();
	//Cube->RenderStencil(Cube, Mirror, ReflectedCube);
	LightSphere->Render();
	Sphere->Render();
	Sphere2->Render();
	Sphere3->Render();
	terrain->draw();
	geomModel->Render();
	tessModel->render();

	for (auto itr = bulletVector.begin(); itr != bulletVector.end(); itr++)
	{
		if ((*itr)->isBulletActive())
			(*itr)->Render();
	}

	if (!WireDraw) { frameBuffer->Draw(); }

	glutSwapBuffers();

}

void Update() {

	GLfloat deltaTime = (GLfloat)glutGet(GLUT_ELAPSED_TIME);
	deltaTime *= 0.001f;

	if (WireDraw)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	Sphere->Update(deltaTime);
	Cube->Update(deltaTime);
	LightSphere->SetPosition(light->GetPosition());


	// Light controls
	if ((KeyCode[(unsigned char)'q'] == KeyState::Pressed) || (KeyCode[(unsigned char)'Q'] == KeyState::Pressed)) {
		light->MoveUp();
	}
	if ((KeyCode[(unsigned char)'e'] == KeyState::Pressed) || (KeyCode[(unsigned char)'E'] == KeyState::Pressed)) {
		light->MoveDown();
	}
	if ((KeyCode[(unsigned char)'a'] == KeyState::Pressed) || (KeyCode[(unsigned char)'A'] == KeyState::Pressed)) {
		light->MoveLeft();
	}
	if ((KeyCode[(unsigned char)'d'] == KeyState::Pressed) || (KeyCode[(unsigned char)'D'] == KeyState::Pressed)) {
		light->MoveRight();
	}
	if ((KeyCode[(unsigned char)'w'] == KeyState::Pressed) || (KeyCode[(unsigned char)'W'] == KeyState::Pressed)) {
		light->MoveForward();
	}
	if ((KeyCode[(unsigned char)'s'] == KeyState::Pressed) || (KeyCode[(unsigned char)'S'] == KeyState::Pressed)) {
		light->MoveBackward();
	}

	// Camera controls
	if ((KeyCode[(unsigned char)'u'] == KeyState::Pressed) || (KeyCode[(unsigned char)'U'] == KeyState::Pressed)) {
		camera->MoveUp();
	}
	if ((KeyCode[(unsigned char)'o'] == KeyState::Pressed) || (KeyCode[(unsigned char)'O'] == KeyState::Pressed)) {
		camera->MoveDown();
	}
	if ((KeyCode[(unsigned char)'j'] == KeyState::Pressed) || (KeyCode[(unsigned char)'J'] == KeyState::Pressed)) {
		camera->MoveLeft();
	}
	if ((KeyCode[(unsigned char)'l'] == KeyState::Pressed) || (KeyCode[(unsigned char)'L'] == KeyState::Pressed)) {
		camera->MoveRight();
	}
	if ((KeyCode[(unsigned char)'i'] == KeyState::Pressed) || (KeyCode[(unsigned char)'I'] == KeyState::Pressed)) {
		camera->MoveForward();
	}
	if ((KeyCode[(unsigned char)'k'] == KeyState::Pressed) || (KeyCode[(unsigned char)'K'] == KeyState::Pressed)) {
		camera->MoveBackward();
	}

	// Wire draw
	if (KeyCode[(unsigned char)'v'] == KeyState::Pressed) {
		WireDraw = true;
	}
	if (KeyCode[(unsigned char)'v'] == KeyState::Released) {
		WireDraw = false;
	}

	// Greyscale
	if (KeyCode[(unsigned char)'g'] == KeyState::Pressed) {
		frameBuffer->SetGreyscale(true);
	}
	if (KeyCode[(unsigned char)'g'] == KeyState::Released) {
		frameBuffer->SetGreyscale(false);
	}

	// Culling
	if (KeyCode[(unsigned char)'c'] == KeyState::Pressed) {
		Culling = false;
	}
	if (KeyCode[(unsigned char)'c'] == KeyState::Released) {
		Culling = true;
	}

	// Reset
	if ((KeyCode[(unsigned char)'r'] == KeyState::Pressed) || (KeyCode[(unsigned char)'R'] == KeyState::Pressed)) {
		camera->SetPosition(vec3(0 + iMoveX, 4 + iMoveY, 8));
		camera->AdjustToTerrainSimple(terrain->GetVertices());
		light->SetPosition(camera->GetPosition() + vec3(0.0f, 4.0f, -5.0f));
		// light->SetPosition(vec3(0 + iMoveX, 4 + iMoveY, 0));
	}

	TimeNew = static_cast<float>((GLfloat)glutGet(GLUT_ELAPSED_TIME));
	bulletTimer += (TimeNew - TimeOld) / 1000.0f;
	std::cout << bulletTimer << endl;

	// Bullet firing
	if ((KeyCode[32] == KeyState::Pressed) && (bulletTimer > bulletFireRate)){

		for (auto itr = bulletVector.begin(); itr != bulletVector.end(); itr++)
		{
			if (((*itr)->isBulletActive()) == false)
			{
				(*itr)->SetBulletActivity(true);
				(*itr)->SetPosition(camera->GetPosition() + vec3(1, 0, 3.0f));
				(*itr)->SetVelocity(normalize(camera->GetCameraForward()) * (*itr)->GetSpeed());
				break;
			}			
		}

		bulletTimer = 0.0f;
	}

	TimeOld = TimeNew;

	// Bullet movement and destruction
	for (auto itr = bulletVector.begin(); itr != bulletVector.end(); itr++)
	{
		if (((*itr)->isBulletActive()) == true)
		{
			(*itr)->Move();

			glm::vec3 pos = (*itr)->GetPosition();

			if (pos.x > 300.0f || pos.x < -300.0f || pos.z > 300.0f || pos.z < -300.0f)
				(*itr)->SetBulletActivity(false);
		}
	}

	// Tess Model
	tessModel->SetDistanceToCamera(tessModel->GetPostion(), camera->GetPosition());

	// Adjust camera to terrain
	//camera->AdjustToTerrain(terrain->GetVertices());
	camera->AdjustToTerrainSimple(terrain->GetVertices());
	//std::cout << camera->GetPosition().x << "," << camera->GetPosition().y << "," << camera->GetPosition().z << endl;

	frameBuffer->SetMotionBlur(false);
//	std::cout << "Motion blur = " << frameBuffer->isMotionBlur() << endl;
}

void KeyDown(unsigned char key, int x, int y) {

	KeyCode[key] = KeyState::Pressed;
	cout << "Key pressed: " << key << "\n";

}

void KeyUp(unsigned char key, int x, int y) {

	KeyCode[key] = KeyState::Released;
	cout << "Key Released: " << key << "\n";

}

void mouse(int button, int button_state, int x, int y) {
#define state ((button_state == GLUT_DOWN) ? DOWN : UP)

	switch (button) {
		case GLUT_LEFT_BUTTON:
			mouseState[MOUSE_LEFT] = state;
			break;
		case GLUT_MIDDLE_BUTTON:
			mouseState[MOUSE_MIDDLE] = state;
			break;

		case GLUT_RIGHT_BUTTON:
			mouseState[MOUSE_RIGHT] = state;
			break;
	}
}

void mousePassiveMove(int x, int y) {
	
	frameBuffer->SetMotionBlur(true);

	if (firstMouse) {
		lastX = x;
		lastY = y;
		firstMouse = false;
	}

	GLfloat xoffset = x - lastX;
	GLfloat yoffset = lastY - y; // Reversed since y coords go from bottom to left
		
	lastX = x;
	lastY = y;

	GLfloat sensitivity = 0.3;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	camera->SetCameraForward(glm::normalize(front));
}

void GeneratePerlinNoiseMap(unsigned int width, unsigned int height, string fileName) {

	// Create an empty PPM image
	RAW image(width, height);

	// Create a PerlinNoise object with the reference permutation vector
	int seed = (rand() % 100);
	PerlinNoise pn(seed);

	unsigned int iteration = 0;

	// Visit every pixel of the image and assign a color generated with Perlin noise

	for (unsigned int y = 0; y < height; ++y) {

		for (unsigned int x = 0; x < width; ++x) {

			double sampleX = (double)x / ((double)width);
			double sampleY = (double)y / ((double)height);

			// Typical Perlin noise
			double n = pn.GenerateNoise(10 * sampleX, 10 * sampleY, 0.8);

			// Map the values to the image
			image.x[iteration] = floor(255 * n);
			image.y[iteration] = floor(255 * n);
			image.z[iteration] = floor(255 * n);

			iteration++;

		}
	}

	// Save the image in a binary PPM file
	image.Write(fileName);

}