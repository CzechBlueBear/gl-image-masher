#include <iostream>
#include "FileUtils.hpp"

template <GLenum TYPE>
GLShader<TYPE>::~GLShader()
{
	glDeleteShader(name);
}

template <GLenum TYPE>
bool GLShader<TYPE>::loadFromString(const std::string &source)
{
	if (!name) gen();

	const char *textPointers[1] = { source.c_str() };
	const GLint lengths[1] = { static_cast<GLint>(source.length()) };
	glShaderSource(name, 1, textPointers, lengths);

	return compile();
}

template <GLenum TYPE>
bool GLShader<TYPE>::load(const std::string &path)
{
	std::string source = loadFileAsString(path);
	if (source.empty()) {
		std::cerr << "shader file empty or unreadable: " << path << std::endl;
		return false;
	}
	return loadFromString(source);
}

template <GLenum TYPE>
bool GLShader<TYPE>::compile()
{
    glCompileShader(name);
    checkGLErrors();

    // check if the compilation was successful
    GLint success = GL_FALSE;
    glGetShaderiv(name, GL_COMPILE_STATUS, &success);
    if (!success) {
    	std::cerr << "error compiling shader (compiler log follows)" << std::endl;
	    GLchar log[1024];
	    glGetShaderInfoLog(name, 1024, nullptr, log);
    	std::cerr << log << std::endl;
    	std::cerr << "(end of compiler log)" << std::endl;
	    return false;
    }

    return true;
}

template <GLenum TYPE>
void GLShader<TYPE>::gen()
{
	if (name)
		panic("object already exists");
	name = glCreateShader(TYPE);
	if (!name)
		panic("unable to generate a GL shader object");
}
