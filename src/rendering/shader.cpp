#include "shader.h"

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

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

void Shader::setInt(const char* name, const int value) const
{
	glUniform1i(getLocation(name), value);
}

void Shader::set2Int(const char* name, const int x, const int y) const
{
	glUniform2i(getLocation(name), x, y);
}

void Shader::set3Int(const char* name, const int x, const int y, const int z) const
{
	glUniform3i(getLocation(name), x, y, z);
}

void Shader::set4Int(const char* name, const int x, const int y, const int z, const int w) const
{
	glUniform4i(getLocation(name), x, y, z, w);
}

void Shader::set2iVector(const char* name, const glm::ivec2& value) const
{
	glUniform2iv(getLocation(name), 1, glm::value_ptr(value));
}

void Shader::set3iVector(const char* name, const glm::ivec3& value) const
{
	glUniform3iv(getLocation(name), 1, glm::value_ptr(value));
}

void Shader::set4iVector(const char* name, const glm::ivec4& value) const
{
	glUniform4iv(getLocation(name), 1, glm::value_ptr(value));
}

void Shader::setUInt(const char* name, const unsigned int value) const
{
	glUniform1ui(getLocation(name), value);
}

void Shader::set2UInt(const char* name, const unsigned int x, const unsigned int y) const
{
	glUniform2ui(getLocation(name), x, y);
}

void Shader::set3UInt(const char* name, const unsigned int x, const unsigned int y, const unsigned int z) const
{
	glUniform3ui(getLocation(name), x, y, z);
}

void Shader::set4UInt(const char* name, const unsigned int x, const unsigned int y, const unsigned int z, const unsigned int w) const
{
	glUniform4ui(getLocation(name), x, y, z, w);
}

void Shader::setFloat(const char* name, const float value) const
{
	glUniform1f(getLocation(name), value);
}

void Shader::set2Float(const char* name, const float x, const float y) const
{
	glUniform2f(getLocation(name), x, y);
}

void Shader::set3Float(const char* name, const float x, const float y, const float z) const
{
	glUniform3f(getLocation(name), x, y, z);
}

void Shader::set4Float(const char* name, const float x, const float y, const float z, const float w) const
{
	glUniform4f(getLocation(name), x, y, z, w);
}

void Shader::set2fVector(const char* name, const glm::vec2& value) const
{
	glUniform2fv(getLocation(name), 1, glm::value_ptr(value));
}

void Shader::set3fVector(const char* name, const glm::vec3& value) const
{
	glUniform3fv(getLocation(name), 1, glm::value_ptr(value));
}

void Shader::set4fVector(const char* name, const glm::vec4& value) const
{
	glUniform4fv(getLocation(name), 1, glm::value_ptr(value));
}

void Shader::setMatrix2f(const char* name, const glm::mat2& value) const
{
	glUniformMatrix2fv(getLocation(name), 1, false, glm::value_ptr(value));
}

void Shader::setMatrix3f(const char* name, const glm::mat3& value) const
{
	glUniformMatrix3fv(getLocation(name), 1, false, glm::value_ptr(value));
}

void Shader::setMatrix4f(const char* name, const glm::mat4& value) const
{
	glUniformMatrix4fv(getLocation(name), 1, false, glm::value_ptr(value));
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