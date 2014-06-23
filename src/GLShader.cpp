#include <iostream>
#include "GLShader.hpp"
#include "FileUtils.hpp"

GLShaderProgram::GLShaderProgram()
{
}

GLShaderProgram::~GLShaderProgram()
{
	glDeleteProgram(name);
}

bool GLShaderProgram::load(const std::string &path)
{
	if (!name) gen();

	vertexShader = std::make_shared<GLVertexShader>();
	fragmentShader = std::make_shared<GLFragmentShader>();

	bool vertexShaderLoaded = vertexShader->load(path + ".vsh");
	bool fragmentShaderLoaded = fragmentShader->load(path + ".fsh");
	if (!vertexShaderLoaded || !fragmentShaderLoaded) {
		vertexShader = nullptr;
		fragmentShader = nullptr;
		return false;
	}

	glAttachShader(name, vertexShader->name);
	glAttachShader(name, fragmentShader->name);

	return link();
}

bool GLShaderProgram::link()
{
	glLinkProgram(name);

    // check if the link was successful
    GLint success = 0;
    glGetProgramiv(name, GL_LINK_STATUS, &success);
    if (success != GL_TRUE) {
    	std::cerr << "error linking shader program (details follow)" << std::endl;

    	// get the link log from the GL driver and print it
       	GLchar log[1024] = { 0 };
    	glGetProgramInfoLog(name, sizeof(log), NULL, log);
    	std::cerr << log << std::endl;
    	return false;
    }

    return true;
}

void GLShaderProgram::bind()
{
	glUseProgram(name);
}

void GLShaderProgram::gen()
{
	if (name)
		panic("object already exists");
	name = glCreateProgram();
	if (!name)
		panic("Unable to generate an OpenGL shader program");
}
