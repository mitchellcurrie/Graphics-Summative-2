#pragma once

#include "FrameBuffer.h"

FrameBuffer::FrameBuffer(GLuint _program)
{
	m_Greyscale = false;
	m_MotionBlur = false;

	program = _program;

	GLfloat vertices[] = {  
								
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		1.0f, -1.0f,  1.0f, 0.0f,
		1.0f,  1.0f,  1.0f, 1.0f
	};

	// Setup screen VAO
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	glBindVertexArray(vao);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
	glBindVertexArray(0);
	glUseProgram(program);

	glUniform1i(glGetUniformLocation(program, "texFramebuffer"), 0);

	// Create framebuffer
	glGenFramebuffers(1, &frameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

	// Generate texture ID to hold color buffer and load texture data 
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Utils::WIDTH, Utils::HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Attach it to currently bound framebuffer object
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

	// Create Renderbuffer Object to hold depth and stencil buffers (won't be sampling these)
	GLuint rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, Utils::WIDTH, Utils::HEIGHT); // Use a single renderbuffer object for both a depth AND stencil buffer.
	glBindRenderbuffer(GL_RENDERBUFFER, 0);


	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // Now actually attach it																							  // Now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::Setup()
{
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	glEnable(GL_DEPTH_TEST);

	GLuint greyscaleLoc = glGetUniformLocation(program, "Greyscale");
	glUniform1f(greyscaleLoc, m_Greyscale);

	GLuint motionblurLoc = glGetUniformLocation(program, "Motionblur");
	glUniform1f(motionblurLoc, m_MotionBlur);
}

void FrameBuffer::Draw()
{
	//-------------------------------------------------------//

	/*GLuint greyscaleLoc = glGetUniformLocation(program, "Greyscale");
	glUniform1f(greyscaleLoc, m_Greyscale);*/


	//// true
	//gl.uniform1i(gl.getUniformLocation("uDoCalculation"), 1);

	//// false
	//gl.uniform1i(gl.getUniformLocation("uDoCalculation"), 0);

	//-------------------------------------------------------//

	// Bind default framebuffer and draw contents of our framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindVertexArray(vao);

	glDisable(GL_DEPTH_TEST);
	glUseProgram(program);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glDrawArrays(GL_TRIANGLES, 0, 6);
}

FrameBuffer::~FrameBuffer()
{
	glDeleteFramebuffers(1, &frameBuffer);
}

void FrameBuffer::SetGreyscale(bool _b)
{
	m_Greyscale = _b;
}

void FrameBuffer::SetMotionBlur(bool _b)
{
	m_MotionBlur = _b;
}

bool FrameBuffer::isGreyscale()
{
	return m_Greyscale;
}

bool FrameBuffer::isMotionBlur()
{
	return m_MotionBlur;
}



