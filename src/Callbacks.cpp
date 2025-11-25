#include <src/Callbacks.h>

Context::Context(int width, int height, Camera* camera)
	: w(width), h(height), camera(camera), lastX(width / 2.0f), lastY(height / 2.0f) {
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	Context* context = (Context*)glfwGetWindowUserPointer(window);
	static bool firstMouse = true;
	if (firstMouse)
	{
		context->lastX = xpos;
		context->lastY = ypos;
		firstMouse = false;
		return;
	}
	float xoffset = xpos - context->lastX;
	float yoffset = context->lastY - ypos;
	context->lastX = xpos;
	context->lastY = ypos;
	context -> camera -> MouseMovement(xoffset, yoffset);
}