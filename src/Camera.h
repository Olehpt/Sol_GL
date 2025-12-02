#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h> 

class Camera {
	glm::vec3 Position, WorldUp, Front;
	float Yaw, Pitch, Sensivity, Speed;
	void MoveForward();
	void MoveBackward();
	void MoveLeft();
	void MoveRight();
public:
	void Update();
	Camera(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90, float pitch = 0, float s1 = 0.1f, float s2 = 0.2f);
	glm::mat4 GetViewMatrix();
	void MouseMovement(float xOffset, float yOffset);
	void ProccessMovement();
};