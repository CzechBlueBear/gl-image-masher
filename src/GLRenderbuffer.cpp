#include "GLFramebuffer.hpp"
#include "panic.hpp"

GLRenderBuffer::GLRenderBuffer()
	: initialized(false)
{
}

GLRenderBuffer::~GLRenderBuffer()
{
	if (name)
		glDeleteRenderbuffers(1, &name);
}

void GLRenderBuffer::gen()
{
	if (!name) {
		glGenRenderbuffers(1, &name);
		if (!name)
			panic("Unable to allocate a GLRenderbuffer");
	}
}

void GLRenderBuffer::init(GLenum format, int width, int height)
{
	// calling init() more than once is redundant but still binds the buffer
	if (initialized) {
		bind();
		return;
	}

	gen();
	glBindRenderbuffer(GL_RENDERBUFFER, name);
	glRenderbufferStorage(GL_RENDERBUFFER, format, width, height);
	initialized = true;
}

void GLRenderBuffer::bind()
{
	if (!name)
		panic("GLRenderBuffer used without proper initialization");

	// bind the existing object
	glBindRenderbuffer(GL_RENDERBUFFER, name);
}

void GLRenderBuffer::bindNone()
{
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}
