#include <glad/glad.h>
#include <GLFW/glfw3.h>  
#include <stb_image.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <src/Shader.h> 
#include <src/Camera.h>
#include <src/Cube.h>
#include <src/Texture.h>
#include <src/Callbacks.h>



int main() { 
   Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f));
   Context context(1920, 1080, &camera);
   //init
   glfwInit();
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

   GLFWwindow* window = glfwCreateWindow(context.w, context.h, "StudyDemo", NULL, NULL);
   glfwSetWindowUserPointer(window, &context);
   if (window == NULL)
   {
       std::cout << "Failed to create GLFW window" << std::endl;
       glfwTerminate();
       return -1;
   }
   glfwMakeContextCurrent(window);
   glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

   if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
   {
       std::cout << "Failed to initialize GLAD" << std::endl;
       return -1;
   }
   //
   glEnable(GL_DEPTH_TEST);
   glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
   glfwSetCursorPosCallback(window, mouse_callback);
   //
   Shader ourShader("shaders/vertexShader.vs", "shaders/fragmentShader.frag");
   Texture texture("assets/img1.jpg");
   glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)context.w/ (float)context.h, 0.1f, 100.0f);
   Cube cube;
   float dt = 0.0f, lf = 0.0f;
   //Render
   glViewport(0, 0, context.w, context.h);
   while (!glfwWindowShouldClose(window))
   {
	   processInput(window);
       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       glm::mat4 model(1.0f), view(1.0f);
       model = glm::rotate(model, glm::radians(-50.0f * (float)glfwGetTime() ), glm::vec3(1.0f, 0.1f, 0.5f));
       view = camera.GetViewMatrix();
       texture.use();
       ourShader.use();
       unsigned int transformUni = glGetUniformLocation(ourShader.ID, "transform");
	   glm::mat4 transform = projection*view*model;
	   glUniformMatrix4fv(transformUni, 1, GL_FALSE, glm::value_ptr(transform));
       
       cube.draw();
       glfwSwapBuffers(window);
       glfwPollEvents();
   }
   cube.remove();
   glfwTerminate();
   return 0;  
}