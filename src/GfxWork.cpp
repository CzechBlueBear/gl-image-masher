#include <iostream>
#include <array>
#include "GfxWork.hpp"
#include "PixelImage.hpp"
#include "Vertex.hpp"
#include "main.hpp"

GfxWork::GfxWork(const std::string &outputDirectory, int workspaceWidth, int workspaceHeight)
	: workspaceWidth(workspaceWidth),
	workspaceHeight(workspaceHeight),
	outputDirectory(outputDirectory)
{
}

GfxWork::~GfxWork()
{
}

void GfxWork::processImage(const std::string &imagePath)
{
	PixelImage sourceImage;
	sourceImage.loadTiff(imagePath);

	if (!texture) {
		texture = std::make_shared<GLTexture2D>();
		texture->load(sourceImage);
		checkGLErrors();
	}

	int imageWidth = sourceImage.getWidth();
	int imageHeight = sourceImage.getHeight();
	if (imageWidth > workspaceWidth)
		imageWidth = workspaceWidth;
	if (imageHeight > workspaceHeight)
		imageHeight = workspaceHeight;

	if (!colorBuffer) {
		colorBuffer = std::make_shared<GLRenderBuffer>();
		colorBuffer->init(GL_RGBA8, workspaceWidth, workspaceHeight);
		checkGLErrors();
	}
	if (!depthBuffer) {
		depthBuffer = std::make_shared<GLRenderBuffer>();
		depthBuffer->init(GL_DEPTH_COMPONENT16, workspaceWidth, workspaceHeight);
		checkGLErrors();
	}
	if (!framebuffer) {
		framebuffer = std::make_shared<GLFrameBuffer>();
		framebuffer->init(colorBuffer, depthBuffer);
		checkGLErrors();
	}

	glViewport(0, 0, imageWidth, imageHeight);

	static const std::array<SimpleTexturedVertex, 4> vertices {
		SimpleTexturedVertex { { -1.0f, -1.0f, 0.0f }, { 0.0f, 1.0f } },		// top left
		{ {  1.0f, -1.0f, 0.0f }, { 1.0f, 1.0f } },
		{ { -1.0f,  1.0f, 0.0f }, { 0.0f, 0.0f } },
		{ {  1.0f,  1.0f, 0.0f }, { 1.0f, 0.0f } },
	};

	static const unsigned short vertexOrder[] {
		0, 1, 2, 2, 1, 3
	};

	if (!shaderProgram) {
		shaderProgram = std::make_shared<GLShaderProgram>();
		shaderProgram->load("shaders/simple");
		checkGLErrors();
	}

	shaderProgram->bind();
	glUniform1i(0, 0);

	if (!vertexBuffer) {
		vertexBuffer = std::make_shared<GLVertexBuffer>();
		vertexBuffer->init(vertices.size()*sizeof(SimpleTexturedVertex), vertices.data(), GL_STATIC_DRAW);
		checkGLErrors();
	}
	if (!indexBuffer) {
		indexBuffer = std::make_shared<GLIndexBuffer>();
		indexBuffer->init(sizeof(vertexOrder), vertexOrder, GL_STATIC_DRAW);
		checkGLErrors();
	}

	checkGLErrors();

	if (!vao) {
		vao = std::make_shared<GLVertexArray>();
		vao->bind();
		vertexBuffer->bind();
		indexBuffer->bind();

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
	} else {
		vao->bind();
	}

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

	checkGLErrors();

	// write it as a file
	PixelImage result;
	result.reset(imageWidth, imageHeight);
	result.screenshot(0, 0, imageWidth, imageHeight);
	if (!result.saveTiff("result.tif")) {
		std::cerr << "error writing result.tiff" << std::endl;
	}
}
