#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

enum CameraMovement
{
	FORWARD,
	BACKWARD,
	RIGHT,
	LEFT,
	UP,
	DOWN
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 4.0f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera
{
public:
	// Camera attributes
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	// Eular angles
	float yaw;
	float pitch;

	// Camera options
	float movementSpeed;
	float mouseSensitivity;
	float zoom;

public:
	Camera(const glm::vec3 position = glm::vec3(0.0f), const glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), const float yaw = YAW, const float pitch = PITCH);

	glm::mat4 getViewMatrix() const;

	void start();
	void update(float dt);
	void processMouseMovement(const double xPos, const double yPos);
	void Camera::processMouseScroll(const double yOffset);

private:
	GLFWwindow* m_Window = nullptr;
	double m_LastX, m_LastY;

private:
	void userInput(const float dt);
	void processKeyboard(const CameraMovement direction, const float deltaTime);
	void updateCameraVectors();
};