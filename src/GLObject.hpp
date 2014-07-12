#ifndef GLBASE_HPP
#define GLBASE_HPP

#include <string>
#include "GLRuntime.hpp"
#include "panic.hpp"

/**
 * Base for all objects that represent a GL object or resource.
 */
class GLObject {
public:

	/**
	 * Constructor.
	 * It initializes the name to 0 and otherwise does no action.
	 */
	GLObject() : name(0) { }

	/**
	 * Destructor (empty).
	 * Derived classes should call the appropriate glDelete...() function
	 * (or similar) here.
	 */
	virtual ~GLObject() { }

	/**
	 * Copy constructor (deleted because GL objects cannot be
	 * directly copied).
	 */
	GLObject(const GLObject &src) = delete;

	/**
	 * Assignment operator (deleted because GL objects cannot be
	 * directly copied).
	 */
	GLObject &operator=(const GLObject &src) = delete;

protected:

	/**
	 * The numeric "name" of the GL object.
	 *
	 * Various types of GL objects can use different namespaces
	 * so the number is not necessarily unique among all GL objects
	 * (only within the given type).
     *
	 * Name of 0 never refers to any existing object and is used
	 * as a predefined empty value.
	 */
	GLuint name;
};

/**
 * Base class for objects that behave according to the GL "binding" concept.
 * Such an object must be bound to the context to affect rendering;
 * unbound objects have no effect. Most non-rendering operations, like
 * property setting/getting, also require the object to be bound.
 *
 * Typically, every type of GL object, and often a subtype (like various
 * kinds of textures), binds to a specific slot, called "target" in OpenGL
 * docs. Binding one object automatically unbinds the previous one.
 * Sometimes, the target is in fact an array of binding points which can be
 * selected with a separate call (e.g. textures).
 *
 * For unbinding a currently bound object without binding another,
 * each derived class shall implement a static method bindNone().
 */
class GLBindableObject : public GLObject {
public:

	/**
	 * Binds the object to its target in the current context.
	 */
	virtual void bind() = 0;
};

#define checkGLErrors() { doCheckGLErrors(__FILE__, __LINE__); }

void doCheckGLErrors(const char *filename, int line);
std::string translateGLError(GLenum error);

#endif
