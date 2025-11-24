#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include <src/Camera.h>

Camera::Camera(glm::vec3 pos, glm::vec3 up, float yaw, float pitch, float s) :Position(pos), WorldUp(up), Yaw(yaw), Pitch(pitch), Sensivity(s) {
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