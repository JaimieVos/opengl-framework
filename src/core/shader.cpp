#include "shader.h"

#include <GL/glew.h>

#include "util/logger.h"

#include <iostream>
#include <fstream>
#include <sstream>

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	std::string vertexCode, fragmentCode;
	std::ifstream vertexShaderFile, fragmentShaderFile;

	vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		vertexShaderFile.open(vertexPath);
		fragmentShaderFile.open(fragmentPath);

		std::stringstream vertexShaderStream, fragmentShaderStream;
		vertexShaderStream << vertexShaderFile.rdbuf();
		fragmentShaderStream << fragmentShaderFile.rdbuf();

		vertexShaderFile.close();
		fragmentShaderFile.close();

		vertexCode = vertexShaderStream.str();
		fragmentCode = fragmentShaderStream.str();
	}
	catch (const std::ifstream::failure& exception)
	{
		logger::error(exception.what());
	}

	const char* vertexShaderCode = vertexCode.c_str();
	const char* fragmentShaderCode = fragmentCode.c_str();

	unsigned int vertex, fragment;

	// Vertex shader compilation
	vertex = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertex, 1, &vertexShaderCode, NULL);
	glCompileShader(vertex);

	parseShader(vertex, ShaderType::SHADER);

	// Fragment shader compilation
	fragment = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragment, 1, &fragmentShaderCode, NULL);
	glCompileShader(fragment);

	parseShader(fragment, ShaderType::SHADER);

	// Shader program linking
	id = glCreateProgram();

	glAttachShader(id, vertex);
	glAttachShader(id, fragment);
	glLinkProgram(id);

	parseShader(id, ShaderType::PROGRAM);

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::bind() const
{
	glUseProgram(id);
}

void Shader::unbind() const
{
	glUseProgram(0);
}

int Shader::getLocation(const std::string& name) const
{
	if (locations.find(name) != locations.end())
		return locations[name];

	const int location = glGetUniformLocation(id, name.c_str());

	locations[name] = location;

	return location;
}

void Shader::parseShader(const unsigned int shaderId, const ShaderType type) const
{
	int success;
	char infolog[1024];

	if (type == ShaderType::SHADER)
		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
	else if (type == ShaderType::PROGRAM)
		glGetShaderiv(shaderId, GL_LINK_STATUS, &success);

	if (!success)
	{
		if (type == ShaderType::SHADER)
		{
			glGetShaderInfoLog(shaderId, 1024, NULL, infolog);
			logger::error("Failed to compile shader");
		}
		else if (type == ShaderType::PROGRAM)
		{
			glGetProgramInfoLog(shaderId, 1024, NULL, infolog);
			logger::error("Failed to link shader program");
		}
		
		logger::error(infolog);
	}
}