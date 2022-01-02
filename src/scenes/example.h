#pragma once

#include "core/scene.h"
#include "core/engine.h"
#include "ogl/shader.h"
#include "ogl/vao.h"

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
	std::shared_ptr<Shader> shader;
	std::shared_ptr<VAO> vao;

	Camera camera{ glm::vec3(0.0f, 0.0f, 3.0f) };
	glm::mat4 projection;
	glm::mat4 model;
	glm::mat4 view;

	float m_Alpha = 0.2f;
};