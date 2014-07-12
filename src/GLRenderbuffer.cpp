#include "GLFramebuffer.hpp"
#include "panic.hpp"

GLRenderBuffer::~GLRenderBuffer()
{
	glDeleteRenderbuffers(1, &name);
}

std::shared_ptr<GLRenderBuffer> GLRenderBuffer::create(GLenum format, int width, int height)
{
	auto that = std::shared_ptr<GLRenderBuffer>(new GLRenderBuffer());
	glBindRenderbuffer(GL_RENDERBUFFER, that->name);
	glRenderbufferStorage(GL_RENDERBUFFER, format, width, height);
	return that;
}

void GLRenderBuffer::bind()
{
	glBindRenderbuffer(GL_RENDERBUFFER, name);
}

void GLRenderBuffer::bindNone()
{
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

GLRenderBuffer::GLRenderBuffer()
{
	glGenRenderbuffers(1, &name);
	if (!name)
		panic("Unable to create a GL renderbuffer: glGenRenderbuffers() failed: " + translateGLError(glGetError()));
}
