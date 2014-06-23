#ifndef GLCONTEXT_HPP
#define GLCONTEXT_HPP

#include <string>
#include "GLObject.hpp"

class GLContext
{
public:

	GLContext(int width, int height, const std::string &title);
	~GLContext();
	void makeCurrent();
	void swapBuffers();

protected:

	/**
	 * Window associated with the context (nullptr if none).
	 */
	GLFWwindow *window = nullptr;
};

#endif
