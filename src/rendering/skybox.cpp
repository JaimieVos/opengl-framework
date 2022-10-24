#include "skybox.h"

#include <stb_image.h>

#include "util/logger.h"

const float skyboxVertices[] =
{
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f
};

const unsigned int skyboxIndices[] =
{
	1, 2, 6,
	6, 5, 1,
	0, 4, 7,
	7, 3, 0,
	4, 5, 6,
	6, 7, 4,
	0, 3, 2,
	2, 1, 0,
	0, 1, 5,
	5, 4, 0,
	3, 7, 6,
	6, 2, 3
};

Skybox::Skybox(const std::vector<std::string>& faces)
	: m_Shader("assets/shaders/skybox.vert", "assets/shaders/skybox.frag")
{
	m_Vao.bind();
	m_Vbo.bind();
	m_Vbo.data(skyboxVertices, sizeof(skyboxVertices));
	
	VertexBufferLayout vbl;
	vbl.push<float>(3);
	
	m_Vao.addBuffer(m_Vbo, vbl);

	m_Ibo.bind();
	m_Ibo.data(skyboxIndices, sizeof(skyboxIndices));

	m_Vao.unbind();
	m_Ibo.unbind();

	texture = loadCubemap(faces);

	m_Shader.bind();
	m_Shader.setInt("u_Skybox", 0);
}

void Skybox::draw(const glm::mat4& view, const glm::mat4& projection)
{
	glDepthFunc(GL_LEQUAL);
	m_Shader.bind();
	m_Shader.setMatrix4f("u_View", view);
	m_Shader.setMatrix4f("u_Projection", projection);

	m_Vao.bind();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	m_Vao.unbind();

	m_Shader.unbind();
	glDepthFunc(GL_LESS);
}

unsigned int Skybox::loadCubemap(const std::vector<std::string>& faces)
{
	unsigned int textureID;
	
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
			);
			stbi_image_free(data);
		}
		else
		{
			logger::error("Cubemap texture failed to load at path: " + faces[i]);
			stbi_image_free(data);
		}
	}
	
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}
