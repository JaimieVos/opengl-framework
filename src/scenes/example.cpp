#include "example.h"

#include <GL/glew.h>

void ExampleScene::start()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	const float vertices[] = {
		// Position		// Color
		0.0f,  0.5f,	1.0f, 0.0f, 0.0f,
	   -0.5f, -0.5f,	0.0f, 1.0f, 0.0f,
		0.5f, -0.5f,	0.0f, 0.0f, 1.0f
	};

	shader = std::make_shared<Shader>("assets/shaders/vertex_shader.vert", "assets/shaders/fragment_shader.frag");
	vao = std::make_shared<VAO>();
	vbo = std::make_shared<VBO>();

	vao->bind();

	vbo->bind();
	vbo->data(vertices, sizeof(vertices));

	VertexBufferLayout vbl;
	vbl.push<float>(2);
	vbl.push<float>(3);

	vao->addBuffer(*vbo, vbl);

	vao->unbind();
}

void ExampleScene::update(const float dt)
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	shader->bind();
	shader->setFloat("u_Alpha", 0.2f);

	vao->bind();
	glDrawArrays(GL_TRIANGLES, 0, 3);
}