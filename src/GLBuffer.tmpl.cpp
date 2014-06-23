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
	if (initialized)
		panic("buffer was already initialized; reinit() must be used");

	gen();
	glBindBuffer(TARGET, name);
	glBufferData(TARGET, size, source, usage);
	initialized = true;
}

template <GLenum TARGET>
void GLBuffer<TARGET>::reinit(size_t size, const void *source)
{
	if (!initialized)
		panic("buffer was not properly initialized (init() was not called)");

	glBindBuffer(TARGET, name);
	glBufferData(TARGET, size, source, 0);
}

template <GLenum TARGET>
void GLBuffer<TARGET>::bind()
{
	if (!initialized)
		panic("buffer was not properly initialized (init() was not called)");
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
		panic("unable to generate a GL Buffer object");
	}
}
