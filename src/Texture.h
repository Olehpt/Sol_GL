#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h> 
#include <string>

class Texture {
public:
	unsigned int ID;
	Texture(const std::string& filepath);
	~Texture();
	void use();
	void remove();
private:
	GLenum getFormat(int nrChannels);
};