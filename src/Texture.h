#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h> 
#include <stb_image.h>

#include <string>

class Texture {
	unsigned int ID;
public:
	Texture(const std::string& filepath);
	void use();
	void remove();
};