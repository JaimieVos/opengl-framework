#include "shader.h"

#include <GL/glew.h>

#include "util/logger.h"
#include "io/file_stream.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	std::string vertexCode = file_stream::readFile(vertexPath);
	std::string fragmentCode = file_stream::readFile(fragmentPath);

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
	m_Id = glCreateProgram();

	glAttachShader(m_Id, vertex);
	glAttachShader(m_Id, fragment);
	glLinkProgram(m_Id);

	parseShader(m_Id, ShaderType::PROGRAM);

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::bind() const
{
	glUseProgram(m_Id);
}

void Shader::unbind() const
{
	glUseProgram(0);
}

int Shader::getLocation(const std::string& name) const
{
	if (m_Locations.find(name) != m_Locations.end())
		return m_Locations[name];

	const int location = glGetUniformLocation(m_Id, name.c_str());

	m_Locations[name] = location;

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