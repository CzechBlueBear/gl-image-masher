#include <iostream>
#include "GLObject.hpp"

void doCheckGLErrors(const char *filename, int line)
{
	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		std::cerr << filename << ":" << line << ": pending GL error: " << translateGLError(error) << std::endl;
	}
}

std::string translateGLError(GLenum error)
{
    switch (error) {
    	case GL_NO_ERROR:			return "GL_NO_ERROR";
        case GL_INVALID_ENUM:       return "GL_INVALID_ENUM";
        case GL_INVALID_VALUE:      return "GL_INVALID_VALUE";
        case GL_INVALID_OPERATION:  return "GL_INVALID_OPERATION";
        case GL_OUT_OF_MEMORY:      return "GL_OUT_OF_MEMORY";
        case GL_STACK_UNDERFLOW:    return "GL_STACK_UNDERFLOW";
        case GL_STACK_OVERFLOW:     return "GL_STACK_OVERFLOW";
        default:					return "(unknown GL error)";
    }
}
