#include "example.h"

#include <GL/glew.h>

#include "ogl/vbo.h"
#include "ogl/ibo.h"
#include "ogl/texture.h"

#include <imgui.h>

void ExampleScene::start()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	const float vertices[] = {
		// Position		// Color				// TexCoords
		0.5f,  0.5f,	0.25f, 0.25f, 0.25f,	1.0f, 1.0f, // Top right
	    0.5f, -0.5f,	0.50f, 0.50f, 0.50f,	1.0f, 0.0f, // Bottom right
	   -0.5f, -0.5f,	0.75f, 0.75f, 0.75f,	0.0f, 0.0f, // Bottom left
	   -0.5f,  0.5f,	1.0f,   1.0f,  1.0f,	0.0f, 1.0f  // Top left
	};

	const unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	shader = std::make_shared<Shader>("assets/shaders/vertex_shader.vert", "assets/shaders/fragment_shader.frag");
	vao = std::make_shared<VAO>();
	VBO vbo;
	IBO ibo;

	vao->bind();

	vbo.bind();
	vbo.data(vertices, sizeof(vertices));

	ibo.bind();
	ibo.data(indices, sizeof(indices));

	VertexBufferLayout vbl;
	vbl.push<float>(2);
	vbl.push<float>(3);
	vbl.push<float>(2);

	vao->addBuffer(vbo, vbl);
	vao->unbind();

	Texture wallTexture("assets/textures/wall.jpg", ImageType::JPG, 0);
	Texture smileTexture("assets/textures/smile.png", ImageType::PNG, 1);

	shader->bind();
	shader->setInt("u_Texture1", 0);
	shader->setInt("u_Texture2", 1);
}

void ExampleScene::update(const float dt)
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	shader->bind();
	shader->setFloat("u_Alpha", m_Alpha);

	ImGui::Begin("Properties");
	ImGui::SliderFloat("Alpha", &m_Alpha, 0, 1);
	ImGui::End();

	vao->bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}