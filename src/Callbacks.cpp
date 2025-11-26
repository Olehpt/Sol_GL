#include <src/Callbacks.h>

Context::Context(int width, int height, Camera* camera)
	: w(width), h(height), camera(camera), lastX(width / 2.0f), lastY(height / 2.0f), buttonDown(false) {
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
	if (!context->buttonDown)
	{
		context->lastX = xpos;
		context->lastY = ypos;
		return;
	}
	float xoffset = xpos - context->lastX;
	float yoffset = context->lastY - ypos;
	context->lastX = xpos;
	context->lastY = ypos;
	context -> camera -> MouseMovement(xoffset, yoffset);
}

void button_callback(GLFWwindow* window, int button, int action, int mods)
{
	Context* context = (Context*)glfwGetWindowUserPointer(window);
	if (button == GLFW_MOUSE_BUTTON_LEFT) 
	{
		if (action == GLFW_PRESS)
			context->buttonDown = true;
		else if (action == GLFW_RELEASE)
			context->buttonDown = false;
	}
}