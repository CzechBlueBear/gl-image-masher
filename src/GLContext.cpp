#include <iostream>
#include "GLContext.hpp"

GLContext::GLContext(int width, int height, const std::string &title)
{
	window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
}

GLContext::~GLContext()
{
	glfwDestroyWindow(window);
}

void GLContext::makeCurrent()
{
	glfwMakeContextCurrent(window);
}

void GLContext::swapBuffers()
{
	glfwSwapBuffers(window);
}
