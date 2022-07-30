#pragma once

#include "core/scene.h"
#include "core/engine.h"
#include "ogl/shader.h"
#include "ogl/mesh.h"

#include <memory>
#include <glm/glm.hpp>

class ExampleScene : public Scene
{
public:
	void start() override;
	void update(const float dt) override;
	void onMousePositionChange(GLFWwindow* window, const double xPos, const double yPos) override;
	void onMouseScroll(GLFWwindow* window, const double xOffset, const double yOffset) override;

private:
	std::shared_ptr<Shader> m_Shader;
	std::shared_ptr<Mesh> m_Mesh;

	Camera m_Camera{ glm::vec3(0.0f, 0.0f, 3.0f) };
	glm::mat4 m_Projection;
	glm::mat4 m_Model;
	glm::mat4 m_View;

	float m_Alpha = 0.2f;
};