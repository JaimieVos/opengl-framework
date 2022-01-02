#include "example.h"

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

#include "ogl/vbo.h"
#include "ogl/ibo.h"
#include "ogl/texture.h"

#include <imgui.h>

void ExampleScene::start()
{
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

	camera.start();

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

	camera.update(dt);

	projection = glm::perspective(glm::radians(camera.zoom), float(SCREEN_WIDTH) / float(SCREEN_HEIGHT), 0.1f, 100.0f);

	view = glm::mat4(1.0f);
	view = camera.getViewMatrix();

	shader->bind();
	shader->setMatrix4f("u_Projection", projection);
	shader->setMatrix4f("u_View", view);

	model = glm::mat4(1.0f);
	shader->setMatrix4f("u_Model", model);

	shader->setFloat("u_Alpha", m_Alpha);

	ImGui::Begin("Properties");
	ImGui::SliderFloat("Alpha", &m_Alpha, 0, 1);
	ImGui::End();

	vao->bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void ExampleScene::onMousePositionChange(GLFWwindow* window, const double xPos, const double yPos)
{
	camera.processMouseMovement(xPos, yPos);
}

void ExampleScene::onMouseScroll(GLFWwindow* window, const double xOffset, const double yOffset)
{
	camera.processMouseScroll(yOffset);
}