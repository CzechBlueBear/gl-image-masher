#ifndef GLVERTEX_ARRAY_HPP
#define GLVERTEX_ARRAY_HPP

#include "GLObject.hpp"

/**
 * A vertex array object (VAO), when bound, monitors and saves settings
 * of vertex attribute arrays for later restoration.
 * Restoring the settings from a VAO is typically faster then setting
 * the arrays every time before drawing.
 *
 * Following settings are stored as the VAO:
 *
 * - for every vertex attribute (even if not used by current shader program):
 *     - whether an attribute array is enabled or disabled for this attribute
 *     - settings of the attribute array (which buffer it is stored in,
 *       value count and type, offset and stride)
 *
 * These settings are guaranteed NOT to be saved in the VAO:
 *
 * - current value of each attribute
 * - vertex buffer currently bound
 */
class GLVertexArray : public GLBindableObject {
public:

	GLVertexArray();
	~GLVertexArray();

	/**
	 * Binds the array.
	 *
	 * If the array has a previously recorded state, it is restored;
	 * if this is the first time the array is bound, the current state
	 * is recorded.
	 *
	 * While bound, the array records every change to vertex array
	 * settings.
	 */
	void bind() override;

	static void bindNone();

protected:

	void gen() override;
};

#endif
