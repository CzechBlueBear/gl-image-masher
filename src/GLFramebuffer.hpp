#ifndef GL_FRAMEBUFFER_HPP
#define GL_FRAMEBUFFER_HPP

#include <memory>
#include "GLObject.hpp"
#include "GLRenderbuffer.hpp"

/**
 * A framebuffer: an in-memory target used for rendering.
 */
class GLFrameBuffer : public GLBindableObject {
public:

	~GLFrameBuffer();

	/**
	 * Creates a new framebuffer object, binds it,
	 * attaches the given color and depth buffer to it,
	 * and returns a pointer to it.
	 */
	static std::shared_ptr<GLFrameBuffer> create(
		std::shared_ptr<GLRenderBuffer> colorBuffer,
		std::shared_ptr<GLRenderBuffer> depthBuffer);

	void bind() override;
	static void bindNone();

protected:

	std::shared_ptr<GLRenderBuffer> colorBuffer;
	std::shared_ptr<GLRenderBuffer> depthBuffer;

	GLFrameBuffer();
};

#endif
