#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "camera.h"

class Scene
{
public:
	virtual void start();
	virtual void update(const float dt);
	virtual void onMousePositionChange(GLFWwindow* window, const double xPos, const double yPos);
	virtual void onMouseScroll(GLFWwindow* window, const double xOffset, const double yOffset);
};