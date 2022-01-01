#pragma once

#include <unordered_map>
#include <string>

enum ShaderType
{
	SHADER,
	PROGRAM
};

class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);

	void bind() const;
	void unbind() const;

private:
	unsigned int id;
	mutable std::unordered_map<std::string, int> locations;

private:
	int getLocation(const std::string& name) const;
	void parseShader(const unsigned int shaderId, const ShaderType type) const;
};