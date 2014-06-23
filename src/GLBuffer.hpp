#ifndef GLBUFFER_HPP
#define GLBUFFER_HPP

#include "GLObject.hpp"

template <GLenum TARGET>
class GLBuffer : public GLBindableObject {
public:

	GLBuffer();
	~GLBuffer();

	/**
	 * Initializes the buffer, setting its size, allocating appropriate
	 * GPU memory, (optionally) filling it with data and setting a hint
	 * about how the buffer will be used.
	 * @note After the call, the buffer is bound.
	 */
	void init(size_t size, const void *source, GLenum usage);

	void bind() override;
	static void bindNone();

protected:

	void gen() override;
};

class GLVertexBuffer : public GLBuffer<GL_ARRAY_BUFFER> {
public:

	GLVertexBuffer() {}
};

class GLIndexBuffer : public GLBuffer<GL_ELEMENT_ARRAY_BUFFER> {
public:

	GLIndexBuffer() {}
};

#include "GLBuffer.tmpl.cpp"

#endif
