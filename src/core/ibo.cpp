#include "ibo.h"

#include <GL/glew.h>

IBO::IBO()
{
	glGenBuffers(1, &m_Id);
}

void IBO::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id);
}

void IBO::unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IBO::data(const void* data, const unsigned int size) const
{
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}