#include <src/Texture.h>
#include <stb_image.h>
#include <iostream>

Texture::Texture(const std::string& filepath) {
	int width, height, nrChannels;
	unsigned char* data = stbi_load(filepath.c_str(), &width, &height, &nrChannels, 0);
	GLenum format = getFormat(nrChannels);
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cerr << "Failed to load texture: " << filepath << "\n";
	}
	stbi_image_free(data);
}

Texture::~Texture() {
	remove();
}

void Texture::use() {
	glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::remove() {
	glDeleteTextures(1, &ID);
}

GLenum Texture::getFormat(int nrChannels) {
	switch (nrChannels) {
	case 1:
		return GL_RED;
	case 3:
		return GL_RGB;
	case 4:
		return GL_RGBA;
	default:
		std::cerr << "Unsupported texture format, using GL_RGB as default; number of channels : " << nrChannels << "\n";
	}
}