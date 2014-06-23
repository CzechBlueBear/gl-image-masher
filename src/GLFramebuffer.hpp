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

	GLFrameBuffer();
	~GLFrameBuffer();
	void bind() override;
	static void bindNone();

	/**
	 * Initializes a framebuffer with two subordinate buffers: the color buffer
	 * and the depth buffer.
	 * @note The call binds the buffer, which stays bound after it returns.
	 */
	void init(std::shared_ptr<GLRenderBuffer> colorBuffer,
		std::shared_ptr<GLRenderBuffer> depthBuffer);

protected:

	std::shared_ptr<GLRenderBuffer> colorBuffer;
	std::shared_ptr<GLRenderBuffer> depthBuffer;

	void gen() override;
};

#endif
