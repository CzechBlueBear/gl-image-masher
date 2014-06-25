#ifndef GFX_WORK_HPP
#define GFX_WORK_HPP

#include <memory>
#include <string>
#include "GLBuffer.hpp"
#include "GLVertexArray.hpp"
#include "GLShader.hpp"
#include "GLTexture.hpp"
#include "GLFramebuffer.hpp"
#include "GLRenderbuffer.hpp"

class GfxWork {
public:

	GfxWork(const std::string &outputDirectory, int workspaceWidth, int workspaceHeight);
	~GfxWork();
	GfxWork(const GfxWork &source) = delete;
	GfxWork &operator=(const GfxWork &source) = delete;
	void processImage(const std::string &imagePath);

protected:

	std::shared_ptr<GLVertexBuffer> vertexBuffer;
	std::shared_ptr<GLIndexBuffer> indexBuffer;
	std::shared_ptr<GLVertexArray> vao;
	std::shared_ptr<GLShaderProgram> shaderProgram;
	std::shared_ptr<GLTexture2D> texture;
	std::shared_ptr<GLFrameBuffer> framebuffer;
	std::shared_ptr<GLRenderBuffer> colorBuffer;
	std::shared_ptr<GLRenderBuffer> depthBuffer;
	int workspaceWidth;
	int workspaceHeight;
	std::string outputDirectory;
};

#endif
