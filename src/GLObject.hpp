#ifndef GLBASE_HPP
#define GLBASE_HPP

#include <string>
#include "GLRuntime.hpp"
#include "panic.hpp"         // for emergency exit from gen() and similar

/**
 * Base for all objects that represent a GL object or resource.
 */
class GLObject {
public:

	/**
	 * Constructor.
	 * The name is initialized to 0 (always an empty object).
	 *
	 * Derived classes can do any non-OpenGL initialization here but
	 * no OpenGL calls should be done here (the constructor can be called
	 * early and it is nontrivial for the programmer to ensure that
	 * OpenGL runtime is initialized at that point).
	 */
	GLObject() : name(0) { }

	/**
	 * Destructor (empty).
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
	 *
	 * The constructor sets name to 0. The gen() call should obtain
	 * a valid number and store it here.
	 */
	GLuint name = 0;

	/**
	 * Set to true if the object is fully initialized, which means
	 * calling (usually) something like init(). Calling gen() typically
	 * is not enough to completely initialize the object.
	 */
	bool initialized = false;

	/**
	 * Generates the underlying OpenGL object
	 * (using one of glGen...() calls).
	 *
	 * Failure of the glGen...() call is considered a fatal error
	 * (it usually means that OpenGL is completely out of resources
	 * or that memory has been corrupted) and panic() is the recommended
	 * course of action.
	 *
	 * @important In most cases, the glGen...() call does not suffice
	 * to have a functional object, and additional initialization is needed.
	 * Derived classes should arrange this initialization on first use,
	 * transparently to the programmer. If this is not possible (usually
	 * because extra information is needed), a public call like init()
	 * or load() shall be provided.
	 */
	virtual void gen() = 0;
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
