#pragma once

#include "camera.h"

#include <glm/glm.hpp>

class Scene
{
public:
	virtual void start();
	virtual void update(const float dt);
	virtual void onMousePositionChange(GLFWwindow* window, const double xPos, const double yPos);
	virtual void onMouseScroll(GLFWwindow* window, const double xOffset, const double yOffset);
};