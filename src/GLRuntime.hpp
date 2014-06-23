#ifndef GL_RUNTIME_HPP
#define GL_RUNTIME_HPP

#include <GL/glew.h>		// glew.h must be included before GLFW
#include <GLFW/glfw3.h>

/* raw GL includes - use these if not using GLFW, GLEW nor SDL
 *
 * #define GL_GLEXT_PROTOTYPES 1	// include GL>1.2
 * #include <GL/gl.h>
 * #include <GL/glext.h>
 */

/**
 * Represents a set of libraries and low-level resources necessary
 * for GL work. This must be the first GL-related object created,
 * and the last one destroyed.
 *
 * Only one instance of this object can exist; the() returns a pointer
 * to the single instance.
 *
 * Recommended usage is putting a GLRuntime object on the stack in main(),
 * which ensures it gets automatically destroyed as main() ends.
 */
class GLRuntime {
public:

	/**
	 * Constructor. Initializes OpenGL and any necessary supporting libraries.
	 * Expected to be called exactly once at very early startup.
	 * Errors in this phase are neutralized using panic().
	 */
	GLRuntime();

	/**
	 * Destructor. Closes windows, deinitializes OpenGL and frees all resources.
	 * Expected to be called at the late termination phase.
	 */
	~GLRuntime();

	/**
	 * Copy constructor (deleted because GLRuntime is a singleton).
	 */
	GLRuntime(const GLRuntime &src) = delete;

	/**
	 * Assignment operator (deleted because GLRuntime is a singleton).
	 */
	GLRuntime &operator=(const GLRuntime &src) = delete;

	/**
	 * Returns a pointer to the single instance of GLRuntime.
	 */
	GLRuntime *the() { return instance; }

protected:

	/**
	 * Pointer to the single existing instance of GLRuntime, or nullptr
	 * if not yet created.
	 */
	static GLRuntime *instance;

	/**
	 * The window (not visible when in "console" mode).
	 */
	GLFWwindow *window;
};

#endif
