#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <src/Shader.h>
class Cube {
public:
	Cube();
	~Cube();
	void draw();
	void remove();
private:
	static unsigned int VBO, VAO;
	static unsigned int texture;
};