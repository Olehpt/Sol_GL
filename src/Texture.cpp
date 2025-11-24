#include <src/Texture.h>
Texture::Texture(const std::string& filepath) {
	int width, height, nrChannels;
	unsigned char* data = stbi_load(filepath.c_str(), &width, &height, &nrChannels, 0);
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	glActiveTexture(GL_TEXTURE0);
	stbi_image_free(data);
}

void Texture::use() {
	glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::remove() {
	glDeleteTextures(1, &ID);
}