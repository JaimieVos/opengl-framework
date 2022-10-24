#include "mesh.h"

#include "vbo.h"
#include "ibo.h"

#include <string>

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture>& textures)
	: m_Vertices(vertices), m_Indices(indices), m_Textures(textures)
{
	setupMesh();
}

void Mesh::draw(const Shader& shader) const
{
	shader.bind();
	m_Vao.bind();

	unsigned int diffuseNr = 0;
	unsigned int specularNr = 0;

	for (unsigned int i = 0; i < m_Textures.size(); i++)
	{
		std::string number;
		std::string name = imageTypeToString(m_Textures[i].getImageType());

		if (name == "diffuse")
			number = std::to_string(diffuseNr++);
		else if (name == "specular")
			number = std::to_string(specularNr++);

		shader.setInt((name + number).c_str(), i);
		m_Textures[i].bind();
	}

	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_Indices.size()), GL_UNSIGNED_INT, 0);
	
	m_Vao.unbind();
}

void Mesh::setupMesh()
{
	m_Vao.bind();

	VBO vbo;
	vbo.bind();
	vbo.data(&m_Vertices[0], static_cast<unsigned int>(m_Vertices.size() * sizeof(Vertex)));

	VertexBufferLayout vbl;
	vbl.push<float>(3);
	vbl.push<float>(3);
	vbl.push<float>(2);

	m_Vao.addBuffer(vbo, vbl);

	IBO ibo;
	ibo.bind();
	ibo.data(&m_Indices[0], static_cast<unsigned int>(m_Indices.size() * sizeof(unsigned int)));

	m_Vao.unbind();
	vbo.unbind();
	ibo.unbind();
}