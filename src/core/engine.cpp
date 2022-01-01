#include "engine.h"

#include "logger.h"

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

	window = glfwCreateWindow(screenWidth, screenHeight, title, NULL, NULL);
	if (window)
	{
		logger::error("Failed to initialize GLFW window");
		return destroy();
	}

	glfwMakeContextCurrent(window);
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
	while (!glfwWindowShouldClose(window))
	{
		update();
	}
}

void Engine::update()
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glfwSwapBuffers(window);
	glfwPollEvents();
}

void Engine::destroy()
{
	if (window != nullptr)
		glfwDestroyWindow(window);

	glfwTerminate();
}