#include "camera.h"

#include "engine.h"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(const glm::vec3 position, const glm::vec3 up, const float yaw, const float pitch)
	: m_Position(position), m_WorldUp(up), m_Yaw(yaw), m_Pitch(pitch), m_Front(glm::vec3(0.0f, 0.0f, -1.0f)), m_MovementSpeed(SPEED), m_MouseSensitivity(SENSITIVITY), m_Zoom(ZOOM)
{
	updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() const
{
	return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
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
	double xOffset = xPos - m_LastX;
	double yOffset = m_LastY - yPos;

	m_LastX = xPos;
	m_LastY = yPos;

	if (glfwGetMouseButton(m_Window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		xOffset *= m_MouseSensitivity;
		yOffset *= m_MouseSensitivity;

		m_Yaw += static_cast<float>(xOffset);
		m_Pitch += static_cast<float>(yOffset);

		if (m_Pitch >= 89.0f)
			m_Pitch = 89.0f;
		if (m_Pitch <= -89.0f)
			m_Pitch = -89.0f;

		updateCameraVectors();
	}
}

void Camera::processKeyboard(const CameraMovement direction, const float deltaTime)
{
	const float cameraSpeed = m_MovementSpeed * deltaTime;

	if (direction == CameraMovement::FORWARD)
		m_Position += m_Front * cameraSpeed;
	if (direction == CameraMovement::LEFT)
		m_Position -= glm::normalize(glm::cross(m_Front, m_Up)) * cameraSpeed;
	if (direction == CameraMovement::BACKWARD)
		m_Position -= m_Front * cameraSpeed;
	if (direction == CameraMovement::RIGHT)
		m_Position += glm::normalize(glm::cross(m_Front, m_Up)) * cameraSpeed;
	if (direction == CameraMovement::UP)
		m_Position += m_Up * cameraSpeed;
	if (direction == CameraMovement::DOWN)
		m_Position -= m_Up * cameraSpeed;
}

void Camera::processMouseScroll(const double yOffset)
{
	m_Zoom -= float(yOffset);

	if (m_Zoom >= 45.0f)
		m_Zoom = 45.0f;
	if (m_Zoom <= 20.0f)
		m_Zoom = 20.0f;
}

void Camera::updateCameraVectors()
{
	glm::vec3 direction;
	direction.x = std::cos(glm::radians(m_Yaw)) * std::cos(glm::radians(m_Pitch));
	direction.y = std::sin(glm::radians(m_Pitch));
	direction.z = std::sin(glm::radians(m_Yaw)) * std::cos(glm::radians(m_Pitch));
	m_Front = glm::normalize(direction);

	m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
	m_Up = glm::normalize(glm::cross(m_Right, m_Front));
}