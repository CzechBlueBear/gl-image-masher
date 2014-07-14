#include <iostream>
#include "debug.hpp"
#include "GLTexture.hpp"

GLTexture::~GLTexture()
{
	glDeleteTextures(1, &name);
}

std::shared_ptr<GLTexture> GLTexture::create2d(
	GLenum internalFormat,
	FilterRule filterRule,
	EdgeRule edgeRule,
	PixelImage &image)
{
	auto that = std::shared_ptr<GLTexture>(new GLTexture(GL_TEXTURE_2D));

	that->bind();

	glTexParameteri(that->target, GL_TEXTURE_MIN_FILTER, filterRule.minFilter);
	glTexParameteri(that->target, GL_TEXTURE_MAG_FILTER, filterRule.magFilter);
	glTexParameteri(that->target, GL_TEXTURE_WRAP_S, edgeRule.edgeX);
	glTexParameteri(that->target, GL_TEXTURE_WRAP_T, edgeRule.edgeY);
	glTexParameteri(that->target, GL_TEXTURE_WRAP_R, edgeRule.edgeZ);

	GLenum imageFormat;
	GLenum imageUnitType;

	switch (image.getFormat()) {
	case PixelImage::Format::RGB:
		imageFormat = GL_RGB;
		imageUnitType = GL_UNSIGNED_BYTE;
		break;

	case PixelImage::Format::RGBA:
		imageFormat = GL_RGBA;
		imageUnitType = GL_UNSIGNED_BYTE;
		break;

	default:
		complain("Unrecognized/unsupported pixel image format");
		return nullptr;
	}

	glTexImage2D(GL_TEXTURE_2D,
		0, internalFormat,
		image.getWidth(), image.getHeight(), 0,
		imageFormat, imageUnitType, image.getData());

	GLenum err = glGetError();
	if (err) {
		complain("Error creating texture from pixel image: glTexImage2D() failed: " + translateGLError(err));
		return nullptr;
	}

	return that;
}

void GLTexture::bind()
{
	glBindTexture(target, name);
}

void GLTexture::unbind()
{
	glBindTexture(target, 0);
}

GLTexture::GLTexture(GLenum target)
	: target(target)
{
	glGenTextures(1, &name);
	if (!name)
		panic("Unable to allocate GL texture: glGenTextures() failed: " + translateGLError(glGetError()));
}
