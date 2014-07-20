#include <iostream>
#include <cassert>
#include "GfxWork.hpp"
#include "PixelImage.hpp"
#include "Vertex.hpp"
#include "main.hpp"

GfxWork::GfxWork(int workspaceWidth, int workspaceHeight)
	: workspaceWidth(workspaceWidth),
	workspaceHeight(workspaceHeight)
{
	corners = {
		SimpleTexturedVertex { { -1.0f, -1.0f, 0.0f }, { 0.0f, 1.0f } },		// top left
		{ {  1.0f, -1.0f, 0.0f }, { 1.0f, 1.0f } },
		{ { -1.0f,  1.0f, 0.0f }, { 0.0f, 0.0f } },
		{ {  1.0f,  1.0f, 0.0f }, { 1.0f, 0.0f } },
	};
}

GfxWork::~GfxWork()
{
}

void GfxWork::processImage(const std::string &imagePath, const std::string &outputPath)
{
	PixelImage sourceImage;
	sourceImage.loadTiff(imagePath);

	if (!texture) {
		texture = GLTexture::create2d(GL_RGB5_A1, GLTexture::FilterRule(), GLTexture::EdgeRule(), sourceImage);
/*
		texture = std::make_shared<GLTexture2D>();
		texture->loadCompressed(sourceImage);
		checkGLErrors();
*/
	}

	int imageWidth = sourceImage.getWidth();
	int imageHeight = sourceImage.getHeight();
	if (imageWidth > workspaceWidth)
		imageWidth = workspaceWidth;
	if (imageHeight > workspaceHeight)
		imageHeight = workspaceHeight;

	if (!colorBuffer) {
		colorBuffer = GLRenderBuffer::create(GL_RGBA8, workspaceWidth, workspaceHeight);
	}
	if (!depthBuffer) {
		depthBuffer = GLRenderBuffer::create(GL_DEPTH_COMPONENT16, workspaceWidth, workspaceHeight);
	}
	if (!framebuffer) {
		framebuffer = GLFrameBuffer::create(colorBuffer, depthBuffer);
	}

	glViewport(0, 0, imageWidth, imageHeight);

	// two triangles form a rectangle
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
		vertexBuffer = GLBuffer::create(GL_ARRAY_BUFFER, corners.size()*sizeof(SimpleTexturedVertex), corners.data(), GL_STATIC_DRAW);
		// vertex buffer is now automatically bound
	}
	if (!indexBuffer) {
		indexBuffer = GLBuffer::create(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertexOrder), vertexOrder, GL_STATIC_DRAW);
		// index buffer is now automatically bound
	}

	checkGLErrors();

	if (!vao) {
		vao = GLVertexArray::create();
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

	// draw the deformed image as two triangles
	shaderProgram->bind();
	//vao->bind();
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
	if (!result.saveTiff(outputPath)) {
		std::cerr << "error writing " << outputPath << std::endl;
	}
}

void GfxWork::setCorner(Corner index, float x, float y)
{
	corners[static_cast<int>(index)].position[0] = x;
	corners[static_cast<int>(index)].position[1] = y;
}
