#include "example.h"

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <imgui.h>

#include "ogl/texture.h"

void ExampleScene::start()
{
	m_Camera.start();
	
	m_Object = std::make_shared<Model>("assets/models/backpack/backpack.obj");

	m_Shader = std::make_shared<Shader>("assets/shaders/vertex_shader.vert", "assets/shaders/fragment_shader.frag");
}

void ExampleScene::update(const float dt)
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_Camera.update(dt);

	m_Projection = glm::perspective(glm::radians(m_Camera.m_Zoom), float(SCREEN_WIDTH) / float(SCREEN_HEIGHT), 0.1f, 100.0f);

	m_View = glm::mat4(1.0f);
	m_View = m_Camera.getViewMatrix();

	m_Shader->bind();
	m_Shader->setMatrix4f("u_Projection", m_Projection);
	m_Shader->setMatrix4f("u_View", m_View);

	m_Model = glm::mat4(1.0f);
	m_Model = glm::scale(m_Model, glm::vec3(0.1f));
	m_Model = glm::rotate(m_Model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	m_Shader->setMatrix4f("u_Model", m_Model);
	
	m_Object->draw(*m_Shader);
}

void ExampleScene::onMousePositionChange(GLFWwindow* window, const double xPos, const double yPos)
{
	m_Camera.processMouseMovement(xPos, yPos);
}

void ExampleScene::onMouseScroll(GLFWwindow* window, const double xOffset, const double yOffset)
{
	m_Camera.processMouseScroll(yOffset);
}