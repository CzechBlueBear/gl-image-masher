#include <iostream>
#include "GLBuffer.hpp"

template <GLenum TARGET>
GLBuffer<TARGET>::GLBuffer()
{
}

template <GLenum TARGET>
GLBuffer<TARGET>::~GLBuffer()
{
	glDeleteBuffers(1, &name);
}

template <GLenum TARGET>
void GLBuffer<TARGET>::init(size_t size, const void *source, GLenum usage)
{
	if (!initialized) {
		gen();
		glBindBuffer(TARGET, name);
		glBufferData(TARGET, size, source, usage);
		initialized = true;
	} else {

		// the object must be bound after init()
		glBindBuffer(TARGET, name);
	}
}

template <GLenum TARGET>
void GLBuffer<TARGET>::bind()
{
	if (!initialized)
		panic("Buffer was not properly initialized");

	glBindBuffer(TARGET, name);
}

template <GLenum TARGET>
void GLBuffer<TARGET>::bindNone()
{
	glBindBuffer(TARGET, 0);
}

template <GLenum TARGET>
void GLBuffer<TARGET>::gen()
{
	if (name)
		panic("object already exists");
	glGenBuffers(1, &name);
	if (!name) {
		panic("Unable to generate a GL Buffer object");
	}
}
