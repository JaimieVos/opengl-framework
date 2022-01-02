#include "example.h"

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <imgui.h>

#include "ogl/vbo.h"
#include "ogl/ibo.h"
#include "ogl/texture.h"

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

	m_Camera.start();

	m_Shader = std::make_shared<Shader>("assets/shaders/vertex_shader.vert", "assets/shaders/fragment_shader.frag");
	m_Vao = std::make_shared<VAO>();
	VBO vbo;
	IBO ibo;

	m_Vao->bind();

	vbo.bind();
	vbo.data(vertices, sizeof(vertices));

	ibo.bind();
	ibo.data(indices, sizeof(indices));

	VertexBufferLayout vbl;
	vbl.push<float>(2);
	vbl.push<float>(3);
	vbl.push<float>(2);

	m_Vao->addBuffer(vbo, vbl);
	m_Vao->unbind();

	Texture wallTexture("assets/textures/wall.jpg", ImageType::JPG, 0);
	Texture smileTexture("assets/textures/smile.png", ImageType::PNG, 1);

	m_Shader->bind();
	m_Shader->setInt("u_Texture1", 0);
	m_Shader->setInt("u_Texture2", 1);
}

void ExampleScene::update(const float dt)
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	m_Camera.update(dt);

	m_Projection = glm::perspective(glm::radians(m_Camera.zoom), float(SCREEN_WIDTH) / float(SCREEN_HEIGHT), 0.1f, 100.0f);

	m_View = glm::mat4(1.0f);
	m_View = m_Camera.getViewMatrix();

	m_Shader->bind();
	m_Shader->setMatrix4f("u_Projection", m_Projection);
	m_Shader->setMatrix4f("u_View", m_View);

	m_Model = glm::mat4(1.0f);
	m_Shader->setMatrix4f("u_Model", m_Model);

	m_Shader->setFloat("u_Alpha", m_Alpha);

	ImGui::Begin("Properties");
	ImGui::SliderFloat("Alpha", &m_Alpha, 0, 1);
	ImGui::End();

	m_Vao->bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void ExampleScene::onMousePositionChange(GLFWwindow* window, const double xPos, const double yPos)
{
	m_Camera.processMouseMovement(xPos, yPos);
}

void ExampleScene::onMouseScroll(GLFWwindow* window, const double xOffset, const double yOffset)
{
	m_Camera.processMouseScroll(yOffset);
}