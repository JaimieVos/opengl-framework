#pragma once

class FBO
{
public:
	FBO();

	void bind() const;
	void unbind() const;

private:
	unsigned int m_Id;
};