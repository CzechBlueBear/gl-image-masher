#ifndef GFX_WORK_HPP
#define GFX_WORK_HPP

#include <array>
#include <memory>
#include <string>
#include "GLBuffer.hpp"
#include "GLVertexArray.hpp"
#include "GLShader.hpp"
#include "GLTexture.hpp"
#include "GLFramebuffer.hpp"
#include "GLRenderbuffer.hpp"
#include "Vertex.hpp"

class GfxWork {
public:

	GfxWork(const std::string &outputDirectory, int workspaceWidth, int workspaceHeight);
	~GfxWork();
	GfxWork(const GfxWork &source) = delete;
	GfxWork &operator=(const GfxWork &source) = delete;
	void processImage(const std::string &imagePath);

	enum class Corner {
		TOP_LEFT = 0,
		TOP_RIGHT = 1,
		BOTTOM_LEFT = 2,
		BOTTOM_RIGHT = 3
	};

	void setCorner(Corner index, float x, float y);

protected:

	std::shared_ptr<GLBuffer> vertexBuffer, indexBuffer;
	std::shared_ptr<GLVertexArray> vao;
	std::shared_ptr<GLShaderProgram> shaderProgram;
	std::shared_ptr<GLTexture2D> texture;
	std::shared_ptr<GLFrameBuffer> framebuffer;
	std::shared_ptr<GLRenderBuffer> colorBuffer;
	std::shared_ptr<GLRenderBuffer> depthBuffer;
	int workspaceWidth;
	int workspaceHeight;
	std::string outputDirectory;

	/// Corners of the image, shifting those allows for various deformation.
	std::array<SimpleTexturedVertex, 4> corners;
};

#endif
