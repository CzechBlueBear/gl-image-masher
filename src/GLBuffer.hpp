#ifndef GLBUFFER_HPP
#define GLBUFFER_HPP

#include <memory>
#include "GLObject.hpp"

class GLBuffer : public GLBindableObject {
public:

	~GLBuffer();

	/**
	 * Creates a buffer, allocates a space for it in GPU memory and optionally
	 * fills it with data. The buffer becomes bound to its specified target.
	 * @return A pointer to the newly created buffer.
	 */
	static std::shared_ptr<GLBuffer> create(GLenum target, size_t size, const void *source, GLenum usage);

	/**
	 * Returns the size of the buffer in bytes.
	 */
	size_t getSize() const { return size; }

	void bind() override;
	void unbind();

protected:

	/**
	 * Constructor.
	 * Stores the target, size, and usage hint, and allocates a name
	 * for the buffer. No memory is allocated for the buffer yet,
	 * and the buffer does *not* get bound.
	 * If the name allocation fails, panic() is invoked.
	 */
	GLBuffer(GLenum target, size_t size, GLenum usage);

	/**
	 * Target as specified in create().
	 */
	GLenum target;

	/**
	 * Buffer size in bytes.
	 */
	size_t size;

	/**
	 * Usage hint as specified in create().
	 */
	GLenum usage;
};

#endif
