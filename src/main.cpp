#include <glad/glad.h>
#include <GLFW/glfw3.h>  
#include <stb_image.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <src/Shader.h> 
#include <src/Camera.h>
#include <src/Cube.h>
#include <src/Texture.h>
#include <src/Callbacks.h>

void Init(GLFWwindow*& window, Context& context);

int main() {
    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    Context context(1920, 1080, &camera);
    GLFWwindow* window = nullptr;
    Init(window, context);
    //imgui setup
    ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
    //
    Shader ourShader("shaders/vertexShader.vs", "shaders/fragmentShader.frag");
    Texture texture1("assets/img1.jpg"), texture2("assets/img2.jpg"), texture3("assets/img3.jpg");
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)context.w / (float)context.h, 0.1f, 100.0f);
	Cube* cubes[3] = {
		new Cube(-1.0f, 0.0f, -1.0f, 0),
		new Cube(2.0f, 0.0f, 0.0f, 1),
		new Cube(0.0f, 1.0f, -2.0f, 2)
	};
    glViewport(0, 0, context.w, context.h);
    while (!glfwWindowShouldClose(window))
    {
	   processInput(window);
	   glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       //cubes rendering
	   for (Cube* cube : cubes) {
           glm::mat4 model(1.0f), view(1.0f);
		   model = glm::translate(model, cube->position);
           model = glm::rotate(model, glm::radians(-50.0f * (float)glfwGetTime()), glm::vec3(1.0f, 0.1f, 0.5f));
           view = camera.GetViewMatrix();
		   if (cube->ID == 0)
			   texture1.use();
		   else if (cube->ID == 1)
			   texture2.use();
		   else
			   texture3.use();
		   ourShader.use();
           unsigned int transformUni = glGetUniformLocation(ourShader.ID, "transform");
           glm::mat4 transform = projection * view * model;
           glUniformMatrix4fv(transformUni, 1, GL_FALSE, glm::value_ptr(transform));
           cube->draw();
	   }
	   //
       glfwSwapBuffers(window);
       glfwPollEvents();
    }
    glfwTerminate();
    return 0;  
}

//-----------------------------------
void Init(GLFWwindow *& window, Context &context) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(context.w, context.h, "StudyDemo", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }
    glfwSetWindowUserPointer(window, &context);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glEnable(GL_DEPTH_TEST);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
}