#include "example.h"

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <imgui.h>
#include <stb_image.h>

#include <vector>
#include <string>

std::vector<std::string> faces = {
	"assets/skybox/right.jpg",
	"assets/skybox/left.jpg",
	"assets/skybox/bottom.jpg",
	"assets/skybox/top.jpg",
	"assets/skybox/front.jpg",
	"assets/skybox/back.jpg"
};

void ExampleScene::start()
{
	m_Camera.start();
	
	m_Object = std::make_shared<Model>("assets/models/backpack/backpack.obj");
	m_Shader = std::make_shared<Shader>("assets/shaders/vertex_shader.vert", "assets/shaders/fragment_shader.frag");

	m_Skybox = std::make_shared<Skybox>(faces);
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
	m_Model = glm::rotate(m_Model, glm::radians(160.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	m_Shader->setMatrix4f("u_Model", m_Model);
	
	m_Object->draw(*m_Shader);
	m_Skybox->draw(glm::mat4(glm::mat3(m_Camera.getViewMatrix())), m_Projection);

	drawUI();
}

void ExampleScene::onMousePositionChange(GLFWwindow* window, const double xPos, const double yPos)
{
	m_Camera.processMouseMovement(xPos, yPos);
}

void ExampleScene::onMouseScroll(GLFWwindow* window, const double xOffset, const double yOffset)
{
	m_Camera.processMouseScroll(yOffset);
}

void ExampleScene::drawUI()
{
	ImGui::Begin("OpenGL Framework", &m_IsGuiOpen, ImGuiWindowFlags_NoSavedSettings);
	ImGui::SetWindowSize(ImVec2(350, SCREEN_HEIGHT - (SCREEN_HEIGHT / 3)));

	if (ImGui::CollapsingHeader("Rendering", NULL))
	{

	}

	if (ImGui::CollapsingHeader("Application info", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::Text("OpenGL Version:");
		ImGui::Text(reinterpret_cast<const char*>(glGetString(GL_VERSION)));
		ImGui::Text("\nHardware info:");
		ImGui::Text(reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
		ImGui::Text("\nFramerate %.2f FPS / Frametime %.4f ms", ImGui::GetIO().Framerate, 1000.0f / ImGui::GetIO().Framerate);
	}

	if (ImGui::CollapsingHeader("About", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::Text("OpenGL Framework by Jaimie Vos");
		ImGui::Text("E-mail:  jaimie.vos@outlook.com");
		ImGui::Text("Twitter: @JaimieVos");
	}

	ImGui::End();
}