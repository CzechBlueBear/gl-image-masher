#include <iostream>
#include "GLVertexArray.hpp"

std::shared_ptr<GLVertexArray> GLVertexArray::create()
{
	auto that = std::shared_ptr<GLVertexArray>(new GLVertexArray());
	return that;
}

void GLVertexArray::bind()
{
	glBindVertexArray(name);
}

void GLVertexArray::bindNone()
{
	glBindVertexArray(0);
}

GLVertexArray::GLVertexArray()
{
	glGenVertexArrays(1, &name);
	if (!name)
		panic("Unable to create a GL vertex array object: glGenVertexArrays() failed: " + translateGLError(glGetError()));
}

GLVertexArray::~GLVertexArray()
{
	glDeleteVertexArrays(1, &name);
}
