#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <memory>
#include "GLObject.hpp"
#include "PixelImage.hpp"

class GLTexture : public GLBindableObject {
public:

	struct FilterRule {
		GLenum minFilter = GL_LINEAR;
		GLenum magFilter = GL_LINEAR;
	};

	/**
	 * The edge rule specifies how the texels with coordinates outside
	 * of texture boundaries are synthesized.
	 */
	struct EdgeRule {
		GLenum edgeX = GL_REPEAT;
		GLenum edgeY = GL_REPEAT;
		GLenum edgeZ = GL_REPEAT;
	};

	virtual ~GLTexture();

	/**
	 * Creates a 2D texture (one that binds to the GL_TEXTURE_2D target).
	 */
	static std::shared_ptr<GLTexture> create2d(
		GLenum internalFormat,
		FilterRule filterRule,
		EdgeRule edgeRule,
		PixelImage &image);

	void bind() override;
	void unbind();

protected:

	/**
	 * The target of the texture (also determines the texture type).
	 */
	GLenum target;

	/**
	 * Constructor. Allocates a GL name for the texture and stores
	 * the target.
	 */
	GLTexture(GLenum target);
};

#endif
