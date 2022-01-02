#include "camera.h"

#include "engine.h"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(const glm::vec3 position, const glm::vec3 up, const float yaw, const float pitch)
	: position(position), worldUp(up), yaw(yaw), pitch(pitch), front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), zoom(ZOOM)
{
	updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() const
{
	return glm::lookAt(position, position + front, up);
}

void Camera::start()
{
	m_Window = Engine::get().getWindow();
	m_LastX = float(SCREEN_WIDTH / 2.0f);
	m_LastY = float(SCREEN_HEIGHT / 2.0f);
}

void Camera::update(float dt)
{
	userInput(dt);
}

void Camera::userInput(const float dt)
{
	if (glfwGetKey(m_Window, GLFW_KEY_W) == GLFW_PRESS)
		processKeyboard(CameraMovement::FORWARD, dt);
	if (glfwGetKey(m_Window, GLFW_KEY_A) == GLFW_PRESS)
		processKeyboard(CameraMovement::LEFT, dt);
	if (glfwGetKey(m_Window, GLFW_KEY_S) == GLFW_PRESS)
		processKeyboard(CameraMovement::BACKWARD, dt);
	if (glfwGetKey(m_Window, GLFW_KEY_D) == GLFW_PRESS)
		processKeyboard(CameraMovement::RIGHT, dt);
	if (glfwGetKey(m_Window, GLFW_KEY_SPACE) == GLFW_PRESS)
		processKeyboard(CameraMovement::UP, dt);
	if (glfwGetKey(m_Window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		processKeyboard(CameraMovement::DOWN, dt);
}

void Camera::processMouseMovement(const double xPos, const double yPos)
{
	float xOffset = xPos - m_LastX;
	float yOffset = m_LastY - yPos;

	m_LastX = xPos;
	m_LastY = yPos;

	if (glfwGetMouseButton(m_Window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		xOffset *= mouseSensitivity;
		yOffset *= mouseSensitivity;

		yaw += static_cast<float>(xOffset);
		pitch += static_cast<float>(yOffset);

		if (pitch >= 89.0f)
			pitch = 89.0f;
		if (pitch <= -89.0f)
			pitch = -89.0f;

		updateCameraVectors();
	}
}

void Camera::processKeyboard(const CameraMovement direction, const float deltaTime)
{
	const float cameraSpeed = movementSpeed * deltaTime;

	if (direction == CameraMovement::FORWARD)
		position += front * cameraSpeed;
	if (direction == CameraMovement::LEFT)
		position -= glm::normalize(glm::cross(front, up)) * cameraSpeed;
	if (direction == CameraMovement::BACKWARD)
		position -= front * cameraSpeed;
	if (direction == CameraMovement::RIGHT)
		position += glm::normalize(glm::cross(front, up)) * cameraSpeed;
	if (direction == CameraMovement::UP)
		position += up * cameraSpeed;
	if (direction == CameraMovement::DOWN)
		position -= up * cameraSpeed;
}

void Camera::processMouseScroll(const double yOffset)
{
	zoom -= float(yOffset);

	if (zoom >= 45.0f)
		zoom = 45.0f;
	if (zoom <= 20.0f)
		zoom = 20.0f;
}

void Camera::updateCameraVectors()
{
	glm::vec3 direction;
	direction.x = std::cos(glm::radians(yaw)) * std::cos(glm::radians(pitch));
	direction.y = std::sin(glm::radians(pitch));
	direction.z = std::sin(glm::radians(yaw)) * std::cos(glm::radians(pitch));
	front = glm::normalize(direction);

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}