#include "vbo.h"

#include "util/logger.h"

std::vector<VertexBufferElement> VertexBufferLayout::getElements() const
{
	return m_Elements;
}

unsigned int VertexBufferLayout::getStride() const
{
	return m_Stride;
}

unsigned int VertexBufferElement::getSizeOfType(unsigned int type)
{
	switch (type)
	{
	case GL_FLOAT: return sizeof(float);
	case GL_UNSIGNED_INT: return sizeof(unsigned int);
	case GL_UNSIGNED_BYTE: return sizeof(unsigned char);
	}

	logger::error("Passed an invalid type to VertexBufferElement::getSizeOfType");

	return 0;
}

VBO::VBO()
{
	glGenBuffers(1, &m_Id);
}

void VBO::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_Id);
}

void VBO::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::data(const void* data, const unsigned int size) const
{
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}