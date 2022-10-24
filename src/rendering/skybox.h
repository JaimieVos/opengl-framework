#pragma once

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <string>

#include "vao.h"
#include "vbo.h"
#include "ibo.h"
#include "shader.h"

class Skybox
{
public:
	Skybox(const std::vector<std::string>& faces);

	void draw(const glm::mat4& view, const glm::mat4& projection);

private:
	Shader m_Shader;
	VAO m_Vao;
	VBO m_Vbo;
	IBO m_Ibo;

	unsigned int texture;

private:
	unsigned int loadCubemap(const std::vector<std::string>& faces);
};