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
	 *
	 * This call should only be used once; it is an error to call it second
	 * time (use reinit() if needed).
	 *
	 * @note The call binds the buffer to its target, and the buffer
	 * remains bound after returning.
	 * @param size Size of the buffer in bytes.
	 * @param source Pointer to a block of source data to copy into the bufer,
	 * or null to leave the buffer uninitialized (with unspecified contents).
	 * @param usage Hint about how the buffer will be used.
	 */
	void init(size_t size, const void *source, GLenum usage);

	/**
	 * Reinitializes the buffer, freeing its old contents, possibly resizing
	 * and/or moving it in GPU memory, and optionally refilling it with data.
	 *
	 * @note The call binds the buffer to its target, and the buffer
	 * remains bound after returning.
	 * @param size New size of the buffer in bytes.
	 * @param source Pointer to a block of source data to copy into the buffer,
	 * or null to leave the buffer uninitialized (with unspecified contents).
	 */
	void reinit(size_t size, const void *source);

	void bind() override;
	static void bindNone();

protected:

	void gen() override;
};

/**
 * A buffer that contains vertex attributes.
 * The contents of the buffer can be either a simple array of values
 * for the attribute (e.g. vectors of 3 floats for vertex position),
 * or an array of structures that can hold multiple (possibly all)
 * attribute values for every vertex.
 */
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
