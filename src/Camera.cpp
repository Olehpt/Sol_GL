#include <src/Camera.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

Camera::Camera(glm::vec3 pos, glm::vec3 up, float yaw, float pitch, float s1, float s2) :Position(pos), WorldUp(up), Yaw(yaw), Pitch(pitch), Sensivity(s1), Speed(s2) {
	Update();
}

glm::mat4 Camera::GetViewMatrix() {
	return glm::lookAt(Position, Position + Front, WorldUp);
}

void Camera::MouseMovement(float xOffset, float yOffset) {
	xOffset *= Sensivity;
	yOffset *= Sensivity;
	Yaw += xOffset;
	Pitch += yOffset;
	if (Pitch > 89.0f)
		Pitch = 89.0f;
	if (Pitch < -89.0f)
		Pitch = -89.0f;
	Update();
}

void Camera::Update() {
	glm::vec3 front;
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	Front = glm::normalize(front);
}

void Camera::MoveForward() {
	Position += Speed * Front;
}
void Camera::MoveBackward() {
	Position -= Speed * Front;
}
void Camera::MoveLeft() {
	Position -= glm::normalize(glm::cross(Front, WorldUp)) * Speed;
}
void Camera::MoveRight() {
	Position += glm::normalize(glm::cross(Front, WorldUp)) * Speed;
}

void Camera::ProccessMovement() {
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_W) == GLFW_PRESS)
		MoveForward();
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_S) == GLFW_PRESS)
		MoveBackward();
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_A) == GLFW_PRESS)
		MoveLeft();
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_D) == GLFW_PRESS)
		MoveRight();
}