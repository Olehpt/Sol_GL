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
#include <src/Context.h>
#include <src/ui/ui.h>

int main() {
    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    Context context(1920, 1080, &camera, nullptr);
    Init(context);
    InitUI(context.window);
    Shader ourShader("shaders/vertexShader.vs", "shaders/fragmentShader.frag");
    Texture* texture1 = new Texture("assets/img1.jpg"), *texture2 = new Texture("assets/img2.jpg"), *texture3 = new Texture("assets/img3.jpg");
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)context.w / (float)context.h, 0.1f, 100.0f);
	Cube* cubes[3] = {
		new Cube(-1.0f, 0.0f, -1.0f, 0, texture1),
		new Cube(2.0f, 0.0f, 0.0f, 1, texture2),
		new Cube(0.0f, 1.0f, -2.0f, 2, texture3)
	};
    glViewport(0, 0, context.w, context.h);
    while (!glfwWindowShouldClose(context.window))
    {
	   processInput(context.window);
	   glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       ourShader.use();
	   for (Cube* cube : cubes) {
           glm::mat4 model(1.0f), view(1.0f);
		   model = glm::translate(model, cube->position);
           model = glm::rotate(model, glm::radians(-50.0f * (float)glfwGetTime()), glm::vec3(1.0f, 0.1f, 0.5f));
           view = camera.GetViewMatrix();
           unsigned int transformUni = glGetUniformLocation(ourShader.ID, "transform");
           glm::mat4 transform = projection * view * model;
           glUniformMatrix4fv(transformUni, 1, GL_FALSE, glm::value_ptr(transform));
           cube->draw();
	   }
       glfwSwapBuffers(context.window);
       glfwPollEvents();
    }
    glfwTerminate();
    return 0;  
}