#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h> 
#include <src/Camera.h>

struct Context {
	const int w, h;
	Camera* camera;
	float lastX, lastY;
	bool buttonDown;
	Context(int width, int height, Camera* camera);
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void button_callback(GLFWwindow* window, int button, int action, int mods);