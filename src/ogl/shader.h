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
	unsigned int m_Id;
	mutable std::unordered_map<std::string, int> m_Locations;

private:
	int getLocation(const std::string& name) const;
	void parseShader(const unsigned int shaderId, const ShaderType type) const;
};