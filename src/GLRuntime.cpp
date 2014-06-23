#include <string>
#include "GLRuntime.hpp"
#include "GLObject.hpp"
#include "panic.hpp"

GLRuntime *GLRuntime::instance = nullptr;

GLRuntime::GLRuntime()
	: window(nullptr)
{
	if (instance) {
		panic("another instance of GLRuntime already exists");
	}
	instance = this;

	// GLFW must be initialized first
	if (!glfwInit()) {
		panic("glfwInit() failed");
	}

	// create the primary window
	glfwWindowHint(GLFW_VISIBLE, false);
	window = glfwCreateWindow(320, 240, "OpenGL Application", nullptr, nullptr);
	if (!window) {
		panic("glfwCreateWindow() failed");
	}

	// attach a GL context to the window (and to this thread)
	glfwMakeContextCurrent(window);

	/*
	 * From this point on, we have a valid GL context backed by a window.
	 * We can't use GL calls yet because we don't know about what calls
	 * are available and at which address; GLEW will determine these.
	 * (Note: in theory, we could use the archaic GL 1.2 calls which are
	 * always preloaded but that would switch our context to compatibility
	 * mode which often behaves strangely.)
	 */

	// init GLEW to get access to the full GL API
	GLenum error = glewInit();
	if (error != GLEW_OK) {
		panic(std::string("glewInit() failed: ") + std::string(reinterpret_cast<const char *>(glewGetErrorString(error))));
	}
}

GLRuntime::~GLRuntime()
{
	glfwTerminate();
	instance = nullptr;
}
