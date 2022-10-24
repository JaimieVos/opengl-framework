#pragma once

#include "vertex.h"
#include "texture.h"
#include "shader.h"
#include "vao.h"

#include <vector>

class Mesh
{
public:
	Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture>& textures);
	
	void draw(const Shader& shader) const;

private:
	VAO m_Vao;

	std::vector<Vertex> m_Vertices;
	std::vector<unsigned int> m_Indices;
	std::vector<Texture> m_Textures;

private:
	void setupMesh();
};