#include "vbo.h"

#include <GL/glew.h>

VBO::VBO()
{
	glGenBuffers(1, &id);
}

void VBO::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VBO::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}