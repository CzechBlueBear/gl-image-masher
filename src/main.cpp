#include <iostream>
#include <memory>
#include "main.hpp"
#include "GLContext.hpp"
#include "GfxWork.hpp"
#include "GLRuntime.hpp"

GfxWork *theGfxWork = nullptr;

int main(int argc, char **argv)
{
	GLRuntime glRuntime;		// must be created before any GL-related objects

	// create the graphics work thread object and execute it
	theGfxWork = new GfxWork();
	theGfxWork->prepare();
	theGfxWork->run();

	// cleanup
	delete theGfxWork;
	theGfxWork = nullptr;
	return 0;
}
