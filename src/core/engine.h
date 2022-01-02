#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "scene.h"

#include <iostream>
#include <memory.h>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 800

class Scene;

class Engine
{
public:
	Engine(const Engine&) = delete;
	static Engine& get();

	GLFWwindow* getWindow() const;
	std::shared_ptr<Scene> getScene() const;

	void init(const char* title, const std::shared_ptr<Scene>& scene);

private:
	GLFWwindow* m_Window = nullptr;
	std::shared_ptr<Scene> m_Scene;

private:
	Engine() {}

	void run();
	void update(const float dt);
	void destroy();
};

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void mouseCursorPositionCallback(GLFWwindow* window, double xPos, double yPos);
void mouseScrollPositionCallback(GLFWwindow* window, double xOffset, double yOffset);