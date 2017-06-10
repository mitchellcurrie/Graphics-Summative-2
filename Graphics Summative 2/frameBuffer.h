#pragma once

#include "Utils.h"


class FrameBuffer
{
public:
	FrameBuffer(GLuint program);
	~FrameBuffer();

	void Setup();
	void Draw();

private:

	GLuint vao, vbo, program, frameBuffer, texture;
};
