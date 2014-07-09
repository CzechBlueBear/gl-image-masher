#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "GLObject.hpp"
#include "PixelImage.hpp"

/**
 * Base class for all textures.
 * @param TARGET The target the texture binds to; this also defines
 * the type of the texture.
 */
template <GLenum TARGET>
class GLTexture : public GLBindableObject {
public:

	GLTexture();
	virtual ~GLTexture();
	void bind() override;
	static void bindNone();

	/**
	 * Sets the minification and magnification filter of the texture.
	 * @note The call binds the texture which remains bound after returning.
	 */
	void setMinMagFilter(GLenum minFilter, GLenum magFilter);

protected:

	void gen() override;
};

class GLTexture2D : public GLTexture<GL_TEXTURE_2D> {
public:

	GLTexture2D();
	~GLTexture2D();

	/**
	 * Loads the specified image into the texture.
	 * A texture loaded this way does not have mipmaps. Initial
	 * magnifying and minifying filter is set to LINEAR.
	 * @note The call binds the texture which remains bound after returning.
	 */
	void load(PixelImage &image);

	void loadCompressed(PixelImage &image);
};

class GLTextureRectangle : public GLTexture<GL_TEXTURE_RECTANGLE> {
public:

	GLTextureRectangle();
	~GLTextureRectangle();
};

#include "GLTexture.tmpl.cpp"

#endif
