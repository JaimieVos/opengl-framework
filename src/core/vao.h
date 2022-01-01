#pragma once

#include "core/vbo.h"

class VAO
{
public:
	VAO();

	void bind() const;
	void unbind() const;
	void addBuffer(const VBO& vbo, const VertexBufferLayout& vbl) const;

private:
	unsigned int m_Id;
};