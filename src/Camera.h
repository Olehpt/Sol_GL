#include <glad/glad.h>
#include <glm/glm.hpp>

class Camera {
	glm::vec3 Position, WorldUp, Front;
	float Yaw, Pitch, Sensivity;
	void Update();
public:
	Camera(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90, float pitch = 0, float s = 0.1f);
	glm::mat4 GetViewMatrix();
	void MouseMovement(float xOffset, float yOffset);
};