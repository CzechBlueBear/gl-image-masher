#include "GLFramebuffer.hpp"

GLFrameBuffer::~GLFrameBuffer()
{
	glDeleteFramebuffers(1, &name);
}

std::shared_ptr<GLFrameBuffer> GLFrameBuffer::create(std::shared_ptr<GLRenderBuffer> colorBuffer,
	std::shared_ptr<GLRenderBuffer> depthBuffer)
{
	auto that = std::shared_ptr<GLFrameBuffer>(new GLFrameBuffer());
	that->colorBuffer = colorBuffer;
	that->depthBuffer = depthBuffer;
	glBindFramebuffer(GL_FRAMEBUFFER, that->name);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, colorBuffer->name);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer->name);
	return that;
}

void GLFrameBuffer::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, name);
}

void GLFrameBuffer::bindNone()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GLFrameBuffer::GLFrameBuffer()
{
	glGenFramebuffers(1, &name);
	if (!name)
		panic("Unable to create a GL framebuffer object: glGenFramebuffers() failed: " + translateGLError(glGetError()));
}
