#include "vao.h"

#include <GL/glew.h>

VAO::VAO()
{
	glGenVertexArrays(1, &m_Id);
}

void VAO::bind() const
{
	glBindVertexArray(m_Id);
}

void VAO::unbind() const
{
	glBindVertexArray(0);
}

void VAO::addBuffer(const VBO& vbo, const VertexBufferLayout& vbl) const
{
	vbo.bind();

	unsigned int offset = 0;

	for (unsigned int i = 0; i < vbl.getElements().size(); i++)
	{
		VertexBufferElement vbe = vbl.getElements()[i];

		glVertexAttribPointer(i, vbe.count, vbe.type, vbe.normalized, vbl.getStride(), (void*)offset);
		glEnableVertexAttribArray(i);

		offset += vbe.count * VertexBufferElement::getSizeOfType(vbe.type);
	}
}
