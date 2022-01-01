#include "vao.h"

#include <GL/glew.h>

VAO::VAO()
{
	glGenVertexArrays(1, &id);
}

void VAO::bind() const
{
	glBindVertexArray(id);
}

void VAO::unbind() const
{
	glBindVertexArray(0);
}