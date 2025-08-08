#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include"Shader.h"

class Camera
{
public:
	glm::vec3 camPos = glm::vec3(0.0f,0.0f,0.0f);
	glm::vec3 Direction = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 camUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 camMatrix = glm::mat4(1.0f);

	int width, height;


	float lastX = 0.0f, lastY = 0.0f;
	float deltaTime = 0.0f;
	
	float FOV, normalFOV;
	float speed = 2.5f;
	float sensitivity = 0.1f;

	Camera(unsigned int width, unsigned int height, float FOV, glm::vec3 position);

	void updateMatrix(float nearPlane, float farPlane);
	void Matrix(Shader& shader, const char* uniform);
	void Inputs(GLFWwindow* window, float deltaTime);
};

