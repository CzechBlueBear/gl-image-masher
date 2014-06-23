#include <iostream>
#include "GLVertexArray.hpp"

GLVertexArray::GLVertexArray()
{
}

GLVertexArray::~GLVertexArray()
{
	glDeleteVertexArrays(1, &name);
}

void GLVertexArray::bind()
{
	if (!name) gen();
	glBindVertexArray(name);
}

void GLVertexArray::bindNone()
{
	glBindVertexArray(0);
}

void GLVertexArray::gen()
{
	if (name)
		panic("object already exists");
	glGenVertexArrays(1, &name);
	if (!name)
		panic("unable to generate a GL vertex array object");
}
