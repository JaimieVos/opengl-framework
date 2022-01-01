#include "engine.h"

#include "util/logger.h"

Engine& Engine::get()
{
    static Engine instance;

    return instance;
}

void Engine::init(const char* title, const int screenWidth, const int screenHeight)
{
	// Initialize GLFW
    glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	m_Window = glfwCreateWindow(screenWidth, screenHeight, title, NULL, NULL);
	if (!m_Window)
	{
		logger::error("Failed to initialize GLFW window");
		return destroy();
	}

	glfwMakeContextCurrent(m_Window);
	glfwSwapInterval(0);

	// Initialize GLEW
	if (glewInit() != GLEW_OK)
	{
		logger::error("Failed to initialize GLEW");
		return destroy();
	}

	run();
}

void Engine::run()
{
	while (!glfwWindowShouldClose(m_Window))
	{
		update();
	}
}

void Engine::update()
{
	if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(m_Window, GLFW_TRUE);

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glfwSwapBuffers(m_Window);
	glfwPollEvents();
}

void Engine::destroy()
{
	if (m_Window != nullptr)
		glfwDestroyWindow(m_Window);

	glfwTerminate();
}