#include <iostream>
#include "GLBuffer.hpp"

GLBuffer::~GLBuffer()
{
	glDeleteBuffers(1, &name);
}

std::shared_ptr<GLBuffer> GLBuffer::create(GLenum target, size_t size, const void *source, GLenum usage)
{
	auto that = std::shared_ptr<GLBuffer>(new GLBuffer(target, size, usage));
	glBindBuffer(target, that->name);
	glBufferData(target, size, source, usage);
	return that;
}

void GLBuffer::bind()
{
	glBindBuffer(target, name);
}

void GLBuffer::unbind()
{
	glBindBuffer(target, 0);
}

GLBuffer::GLBuffer(GLenum target, size_t size, GLenum usage)
	: target(target), size(size), usage(usage)
{
	glGenBuffers(1, &name);
	if (!name)
		panic("Unable to create a GL buffer object: glGenBuffers() failed: " + translateGLError(glGetError()));
}
