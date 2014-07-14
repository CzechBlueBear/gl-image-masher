#ifndef GL_RENDERBUFFER_HPP
#define GL_RENDERBUFFER_HPP

#include <memory>
#include "GLObject.hpp"

class GLRenderBuffer : public GLBindableObject {
public:

	~GLRenderBuffer();

	/**
	 * Creates a new renderbuffer, allocates its memory, and binds it.
	 * @param format Renderbuffer format.
	 * @param width Width in pixels.
	 * @param height Height in pixels.
	 * @return A shared pointer to the new renderbuffer, or null
	 * if an error occurred.
	 */
	static std::shared_ptr<GLRenderBuffer> create(GLenum format, int width, int height);

	void bind() override;
	static void bindNone();

	friend class GLFrameBuffer;

protected:

	/**
	 * Constructor.
	 * Allocates the name for the render buffer but does not allocate
	 * any memory for it yet. The buffer is not bound.
	 */
	GLRenderBuffer();
};

#endif
