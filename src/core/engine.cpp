#include "engine.h"

#include "util/logger.h"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#define GLSL_VERSION "#version 330"

Engine& Engine::get()
{
    static Engine instance;

    return instance;
}

void Engine::init(const char* title, const int screenWidth, const int screenHeight, const std::shared_ptr<Scene>& scene)
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

	// ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();

	ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
	ImGui_ImplOpenGL3_Init(GLSL_VERSION);

	ImGui::StyleColorsClassic();

	m_Scene = scene;

	run();
}

void Engine::run()
{
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	try
	{
		m_Scene->start();

		while (!glfwWindowShouldClose(m_Window))
		{
			deltaTime = static_cast<float>(glfwGetTime() - lastFrame);
			lastFrame = static_cast<float>(glfwGetTime());

			update(deltaTime);
		}
	}
	catch (const std::exception& exception)
	{
		logger::error(exception.what());
		destroy();
	}
}

void Engine::update(const float dt)
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(m_Window, GLFW_TRUE);

	m_Scene->update(dt);

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(m_Window);
	glfwPollEvents();
}

void Engine::destroy()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	if (m_Window != nullptr)
		glfwDestroyWindow(m_Window);

	glfwTerminate();
}