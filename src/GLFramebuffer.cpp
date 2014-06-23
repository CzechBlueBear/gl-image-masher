#include "GLFramebuffer.hpp"

GLFrameBuffer::GLFrameBuffer()
{
}

GLFrameBuffer::~GLFrameBuffer()
{
	glDeleteFramebuffers(1, &name);
}

void GLFrameBuffer::gen()
{
	if (name)
		panic("object already exists");
	glGenFramebuffers(1, &name);
	if (!name)
		panic("Unable to generate an OpenGL Framebuffer object");
}

void GLFrameBuffer::bind()
{
	if (!name) gen();
	glBindFramebuffer(GL_FRAMEBUFFER, name);
}

void GLFrameBuffer::bindNone()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void GLFrameBuffer::init(std::shared_ptr<GLRenderBuffer> colorBuffer,
	std::shared_ptr<GLRenderBuffer> depthBuffer)
{
	bind();
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, colorBuffer->name);
	this->colorBuffer = colorBuffer;
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer->name);
	this->depthBuffer = depthBuffer;
}
