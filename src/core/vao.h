#pragma once

class VAO
{
public:
	VAO();

	void bind() const;
	void unbind() const;

private:
	unsigned int id;
};