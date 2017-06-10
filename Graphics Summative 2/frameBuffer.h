#pragma once

#include "Utils.h"


class FrameBuffer
{
public:
	FrameBuffer(GLuint program);
	~FrameBuffer();

	void Setup();
	void Draw();

	void SetGreyscale(bool _b);
	void SetMotionBlur(bool _b);

	bool isGreyscale();
	bool isMotionBlur();


private:

	GLuint vao, vbo, program, frameBuffer, texture;
	bool m_MotionBlur;
	bool m_Greyscale;
};
