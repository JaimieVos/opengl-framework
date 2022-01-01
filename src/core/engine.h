#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Engine
{
public:
	Engine(const Engine&) = delete;
	static Engine& get();

	void init(const char* title, const int screenWidth, const int screenHeight);

private:
	GLFWwindow* window = nullptr;

private:
	Engine() {}

	void run();
	void update();
	void destroy();
};