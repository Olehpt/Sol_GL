#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <src/Shader.h>
#include <src/Texture.h>

class Cube {
public:
	glm::vec3 position;
	unsigned int ID;
	Cube(float x = 0, float y = 0, float z = 0, unsigned int id=0, Texture* t = nullptr);
	~Cube();
	void draw();
	void remove();
private:
	static unsigned int VBO, VAO;
	Texture* texture;
};