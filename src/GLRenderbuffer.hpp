#ifndef GL_RENDERBUFFER_HPP
#define GL_RENDERBUFFER_HPP

#include "GLObject.hpp"

class GLRenderBuffer : public GLBindableObject {
public:

	GLRenderBuffer();
	~GLRenderBuffer();

	/**
	 * Initializes the buffer, setting its format and size and allocating
	 * appropriate memory. The initial contents of the buffer are undefined.
	 *
	 * @note This call causes the buffer to be bound. Multiple calls to
	 * init() have no effect (except for binding the buffer).
	 */
	void init(GLenum format, int width, int height);

	void bind() override;
	static void bindNone();

	friend class GLFrameBuffer;

protected:

	/** True if the object is fully initialized. */
	bool initialized;

	void gen() override;
};

#endif
