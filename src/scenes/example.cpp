#include "example.h"

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <imgui.h>

#include "ogl/texture.h"

void ExampleScene::start()
{
	const Vertex vertices[]{
		Vertex { glm::vec2(0.5f, 0.5f),   glm::vec3(0.25f, 0.25f, 0.25f), glm::vec2(1.0f, 1.0f) },
		Vertex { glm::vec2(0.5f, -0.5f),  glm::vec3(0.50f, 0.50f, 0.50f), glm::vec2(1.0f, 0.0f) },
		Vertex { glm::vec2(-0.5f, -0.5f), glm::vec3(0.75f, 0.75f, 0.75f), glm::vec2(0.0f, 0.0f) },
		Vertex { glm::vec2(-0.5f, 0.5f),  glm::vec3(1.0f,   1.0f,  1.0f), glm::vec2(0.0f, 1.0f) }
	};

	const unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	const Texture textures[] {
		Texture { "assets/textures/wall.jpg", ImageType::DIFFUSE, ImageFormat::JPG, 0 },
		Texture { "assets/textures/smile.png", ImageType::DIFFUSE, ImageFormat::PNG, 1 }
	};

	std::vector<Vertex> verts(std::begin(vertices), std::end(vertices));
	std::vector<unsigned int> ind(std::begin(indices), std::end(indices));
	std::vector<Texture> tex(std::begin(textures), std::end(textures));

	m_Mesh = std::make_shared<Mesh>(verts, ind, tex);

	m_Camera.start();

	m_Shader = std::make_shared<Shader>("assets/shaders/vertex_shader.vert", "assets/shaders/fragment_shader.frag");
}

void ExampleScene::update(const float dt)
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	m_Camera.update(dt);

	m_Projection = glm::perspective(glm::radians(m_Camera.m_Zoom), float(SCREEN_WIDTH) / float(SCREEN_HEIGHT), 0.1f, 100.0f);

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

	m_Mesh->draw(*m_Shader);
}

void ExampleScene::onMousePositionChange(GLFWwindow* window, const double xPos, const double yPos)
{
	m_Camera.processMouseMovement(xPos, yPos);
}

void ExampleScene::onMouseScroll(GLFWwindow* window, const double xOffset, const double yOffset)
{
	m_Camera.processMouseScroll(yOffset);
}