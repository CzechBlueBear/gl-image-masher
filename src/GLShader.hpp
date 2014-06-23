#ifndef GLSHADER_HPP
#define GLSHADER_HPP

#include <memory>
#include "GLObject.hpp"

template <GLenum TYPE>
class GLShader : public GLObject {
public:

	GLShader() {}
	~GLShader();
	bool load(const std::string &path);
	bool loadFromString(const std::string &source);

protected:

	void gen() override;

	/**
	 * Compiles the shader. Called automatically from load()
	 * and loadFromString().
	 * Returns true on success, false on failure.
	 */
	bool compile();

	friend class GLShaderProgram;
};

class GLVertexShader : public GLShader<GL_VERTEX_SHADER> {
public:

	GLVertexShader() {}
};

class GLFragmentShader : public GLShader<GL_FRAGMENT_SHADER> {
public:

	GLFragmentShader() {}
};

/**
 * A complete shader program that can be bound into context for processing
 * rendering. It must contain at least the vertex and fragment shader.
 */
class GLShaderProgram : public GLBindableObject {
public:

	GLShaderProgram();
	~GLShaderProgram();
	bool load(const std::string &path);
	void bind() override;

protected:

	std::shared_ptr<GLVertexShader> vertexShader;
	std::shared_ptr<GLFragmentShader> fragmentShader;

	void gen() override;
	bool link();
};

#include "GLShader.tmpl.cpp"

#endif
