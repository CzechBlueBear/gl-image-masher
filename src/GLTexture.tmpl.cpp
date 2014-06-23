#include "panic.hpp"

template <GLenum TARGET>
GLTexture<TARGET>::GLTexture()
{
}

template <GLenum TARGET>
GLTexture<TARGET>::~GLTexture()
{
	glDeleteTextures(1, &name);
}

template <GLenum TARGET>
void GLTexture<TARGET>::bind()
{
	if (!name) gen();
	glBindTexture(TARGET, name);
}

template <GLenum TARGET>
void GLTexture<TARGET>::bindNone()
{
	glBindTexture(TARGET, 0);
}

template <GLenum TARGET>
void GLTexture<TARGET>::setMinMagFilter(GLenum minFilter, GLenum magFilter)
{
	bind();
	glTexParameterf(TARGET, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameterf(TARGET, GL_TEXTURE_MAG_FILTER, magFilter);
}

template <GLenum TARGET>
void GLTexture<TARGET>::gen()
{
	if (name)
		panic("object already exists");
	glGenTextures(1, &name);
	if (!name)
		panic("Unable to generate a GL Texture object");
}
