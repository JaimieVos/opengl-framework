#pragma once

class IBO
{
public:
	IBO();

	void bind() const;
	void unbind() const;
	void data(const void* data, const unsigned int size) const;

private:
	unsigned int m_Id;
};