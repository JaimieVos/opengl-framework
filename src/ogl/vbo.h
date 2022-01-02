#pragma once

#include <GL/glew.h>

#include <vector>

struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int getSizeOfType(unsigned int type);
};

class VertexBufferLayout
{
public:
	std::vector<VertexBufferElement> getElements() const;
	unsigned int getStride() const;

	template<typename T>
	void push(const unsigned int count) = delete;

	template<>
	void push<float>(const unsigned int count)
	{
		VertexBufferElement e { GL_FLOAT, count, GL_FALSE };

		m_Elements.push_back(e);
		m_Stride += count * VertexBufferElement::getSizeOfType(GL_FLOAT);
	}

	template<>
	void push<unsigned int>(const unsigned int count)
	{
		VertexBufferElement e{ GL_UNSIGNED_INT, count, GL_FALSE };

		m_Elements.push_back(e);
		m_Stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT);
	}

	template<>
	void push<unsigned char>(const unsigned int count)
	{
		VertexBufferElement e{ GL_UNSIGNED_BYTE, count, GL_TRUE };

		m_Elements.push_back(e);
		m_Stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE);
	}

private:
	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride = 0;
};

class VBO
{
public:
	VBO();

	void bind() const;
	void unbind() const;
	void data(const void* data, const unsigned int size) const;

private:
	unsigned int m_Id;
};