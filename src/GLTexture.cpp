#include <iostream>
#include "GLTexture.hpp"

GLTexture2D::GLTexture2D()
{
}

GLTexture2D::~GLTexture2D()
{
}

void GLTexture2D::load(PixelImage &image)
{
	// Reset the filtering (because if it was set to mipmaps, which is the default,
	// loading just one image would make the texture incomplete and unusable)
	// This call also binds the texture.
	setMinMagFilter(GL_LINEAR, GL_LINEAR);

	// upload the image to the (currently bound) texture, resetting its size
	// and replacing old contents
	switch (image.getFormat()) {
	case image.Format::RGB:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
			image.getWidth(), image.getHeight(), 0,
			GL_RGB, GL_UNSIGNED_BYTE, image.getData());
		break;

	case image.Format::RGBA:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
			image.getWidth(), image.getHeight(), 0,
			GL_RGBA, GL_UNSIGNED_BYTE, image.getData());
		break;

	default:
		std::cerr << "unexpected source image format" << std::endl;
	}
}

GLTextureRectangle::GLTextureRectangle()
{
}

GLTextureRectangle::~GLTextureRectangle()
{
}
