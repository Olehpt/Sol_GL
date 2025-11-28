#include <src/Context.h>
#include <iostream>

Context::Context(int width, int height, Camera* camera, GLFWwindow* w)
	: w(width), h(height), camera(camera), lastX(width / 2.0f), lastY(height / 2.0f), buttonDown(false), window(w) {
}

void Init(Context& context) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	context.window = glfwCreateWindow(context.w, context.h, "StudyDemo", NULL, NULL);
	if (context.window == NULL)
	{
		std::cout << "Failed to create GLFW window\n";
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(context.window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD\n";
		return;
	}
	glfwSetWindowUserPointer(context.window, &context);
	glfwSetFramebufferSizeCallback(context.window, framebuffer_size_callback);
	glEnable(GL_DEPTH_TEST);
	glfwSetInputMode(context.window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwSetCursorPosCallback(context.window, mouse_callback);
	glfwSetMouseButtonCallback(context.window, button_callback);
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