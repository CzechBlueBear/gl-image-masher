#include <iostream>
#include <memory>
#include "main.hpp"
#include "GLContext.hpp"
#include "GfxWork.hpp"
#include "GLRuntime.hpp"

//GfxWork *theGfxWork = nullptr;

int main(int argc, char **argv)
{
	GLRuntime glRuntime;		// must be created before any GL-related objects

	// create the graphics work thread object and execute it
	std::shared_ptr<GfxWork> theGfxWork = std::make_shared<GfxWork>(10000, 10000);

	// example of deformation
	theGfxWork->setCorner(GfxWork::Corner::TOP_LEFT, -0.6f, -0.6f);
	theGfxWork->setCorner(GfxWork::Corner::TOP_RIGHT, 0.8f, -1.0f);
	theGfxWork->setCorner(GfxWork::Corner::BOTTOM_LEFT, -1.0f, 0.9f);

	theGfxWork->processImage("input.tif", "result.tif");

	// cleanup
	return 0;
}
