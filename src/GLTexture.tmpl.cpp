#include "panic.hpp"

template <GLenum TARGET>
GLTexture<TARGET>::GLTexture()
{
	glGenTextures(1, &name);
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
void GLTexture<TARGET>::bound_setMinFilter(GLenum minFilter)
{
	glTexParameterf(TARGET, GL_TEXTURE_MIN_FILTER, minFilter);
}

template <GLenum TARGET>
void GLTexture<TARGET>::bound_setMagFilter(GLenum magFilter)
{
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
