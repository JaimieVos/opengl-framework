#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "scene.h"

#include <iostream>
#include <memory.h>

class Engine
{
public:
	Engine(const Engine&) = delete;
	static Engine& get();

	void init(const char* title, const int screenWidth, const int screenHeight, const std::shared_ptr<Scene>& scene);

private:
	GLFWwindow* m_Window = nullptr;
	std::shared_ptr<Scene> m_Scene;

private:
	Engine() {}

	void run();
	void update(const float dt);
	void destroy();
};