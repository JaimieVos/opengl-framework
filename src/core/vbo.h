#pragma once

class VBO
{
public:
	VBO();

	void bind() const;
	void unbind() const;

private:
	unsigned int id;
};