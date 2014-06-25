#include <iostream>
#include <array>
#include "GfxWork.hpp"
#include "PixelImage.hpp"
#include "Vertex.hpp"
#include "main.hpp"

GfxWork::GfxWork()
{
	vertexBuffer = std::make_shared<GLVertexBuffer>();
	indexBuffer = std::make_shared<GLIndexBuffer>();
	vao = std::make_shared<GLVertexArray>();
	shaderProgram = std::make_shared<GLShaderProgram>();
	texture = std::make_shared<GLTexture2D>();
	framebuffer = std::make_shared<GLFrameBuffer>();
	colorBuffer = std::make_shared<GLRenderBuffer>();
	depthBuffer = std::make_shared<GLRenderBuffer>();
}

GfxWork::~GfxWork()
{
}

void GfxWork::prepare()
{
	PixelImage sourceImage;
	sourceImage.loadTiff("input.tif");

	texture->load(sourceImage);

	workspaceWidth = sourceImage.getWidth();
	workspaceHeight = sourceImage.getHeight();

	colorBuffer->init(GL_RGBA8, workspaceWidth, workspaceHeight);
	checkGLErrors();
	depthBuffer->init(GL_DEPTH_COMPONENT16, workspaceWidth, workspaceHeight);
	checkGLErrors();
	framebuffer->init(colorBuffer, depthBuffer);
	checkGLErrors();

	glViewport(0, 0, workspaceWidth, workspaceHeight);

	static const std::array<SimpleTexturedVertex, 4> vertices {
		SimpleTexturedVertex { { -1.0f, -1.0f, 0.0f }, { 0.0f, 1.0f } },		// top left
		{ {  1.0f, -1.0f, 0.0f }, { 1.0f, 1.0f } },
		{ { -1.0f,  1.0f, 0.0f }, { 0.0f, 0.0f } },
		{ {  1.0f,  1.0f, 0.0f }, { 1.0f, 0.0f } },
	};

	static const unsigned short vertexOrder[] {
		0, 1, 2, 2, 1, 3
	};

/*
	// An array of 3 vectors which represents 3 vertices
	static const GLfloat triangleVertices[] = {
	   -1.0f, -1.0f, 0.0f,
	   1.0f, -1.0f, 0.0f,
	   0.0f,  1.0f, 0.0f,
	};
*/

	shaderProgram->load("shaders/simple");
	shaderProgram->bind();

	glUniform1i(0, 0);

	vao->bind();
	vertexBuffer->init(vertices.size()*sizeof(SimpleTexturedVertex), vertices.data(), GL_STATIC_DRAW);
	indexBuffer->init(sizeof(vertexOrder), vertexOrder, GL_STATIC_DRAW);

	checkGLErrors();

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
	   0,                  // attribute 0 is position
	   3, GL_FLOAT,        // type: 3x float
	   GL_FALSE,           // normalized?

	   // stride and offset of the values in the array
	   sizeof(SimpleTexturedVertex),
	   (void*)(offsetof(SimpleTexturedVertex, position))
	);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1,					// attribute 1 is texture coordinate
		2, GL_FLOAT,		// type: 2x float
		GL_FALSE,			// do not normalize

		// stride and offset of the values in the array
		sizeof(SimpleTexturedVertex),
		(void*)(offsetof(SimpleTexturedVertex, textureCoordinates))
	);

	checkGLErrors();
}

void GfxWork::run()
{
	checkGLErrors();

	// clear the scene
	glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glEnable(GL_CULL_FACE);

	checkGLErrors();

	// Draw the triangle !
	shaderProgram->bind();
	vao->bind();
	//glDrawArrays(GL_TRIANGLE_STRIP, 0, 5);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);
	vao->bindNone();

	checkGLErrors();

	// ensure the image is fully rendered
	glFlush();
	//context->swapBuffers();

	checkGLErrors();

	// write it as a file
	PixelImage result;
	result.reset(workspaceWidth, workspaceHeight);
	result.screenshot(0, 0, workspaceWidth, workspaceHeight);
	if (!result.saveTiff("result.tif")) {
		std::cerr << "error writing result.tiff" << std::endl;
	}
}
