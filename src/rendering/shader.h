#pragma once

#include <glm/glm.hpp>
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

	void setInt(const char* name, const int value) const;
	void set2Int(const char* name, const int x, const int y) const;
	void set3Int(const char* name, const int x, const int y, const int z) const;
	void set4Int(const char* name, const int x, const int y, const int z, const int w) const;
	void set2iVector(const char* name, const glm::ivec2& value) const;
	void set3iVector(const char* name, const glm::ivec3& value) const;
	void set4iVector(const char* name, const glm::ivec4& value) const;

	void setUInt(const char* name, const unsigned int value) const;
	void set2UInt(const char* name, const unsigned int x, const unsigned int y) const;
	void set3UInt(const char* name, const unsigned int x, const unsigned int y, const unsigned int z) const;
	void set4UInt(const char* name, const unsigned int x, const unsigned int y, const unsigned int z, const unsigned int w) const;

	void setFloat(const char* name, const float value) const;
	void set2Float(const char* name, const float x, const float y) const;
	void set3Float(const char* name, const float x, const float y, const float z) const;
	void set4Float(const char* name, const float x, const float y, const float z, const float w) const;
	void set2fVector(const char* name, const glm::vec2& value) const;
	void set3fVector(const char* name, const glm::vec3& value) const;
	void set4fVector(const char* name, const glm::vec4& value) const;
	void setMatrix2f(const char* name, const glm::mat2& value) const;
	void setMatrix3f(const char* name, const glm::mat3& value) const;
	void setMatrix4f(const char* name, const glm::mat4& value) const;

private:
	unsigned int m_Id;
	mutable std::unordered_map<std::string, int> m_Locations;

private:
	int getLocation(const std::string& name) const;
	void parseShader(const unsigned int shaderId, const ShaderType type) const;
};