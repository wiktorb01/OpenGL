#include "Camera.h"

// Camera constructor: sets initial width, height, and position
Camera::Camera(unsigned int width, unsigned int height, float FOV, glm::vec3 position)
{
	Camera::FOV = FOV;
    normalFOV = FOV;
	Camera::width = width;
	Camera::height = height;
	camPos = position;
}

// Sets the combined projection and view matrix in the shader
void Camera::updateMatrix(float nearPlane, float farPlane, unsigned int width, unsigned int height)
{
    view = glm::mat4(1.0f);
    projection = glm::mat4(1.0f);

    // Create view matrix using camera position and orientation
    view = glm::lookAt(camPos, camPos + Direction, camUp);
    // Create projection matrix using perspective
    projection = glm::perspective(glm::radians(FOV), (float)width / height, nearPlane, farPlane);
}

// Updates the camera matrix in the shader
void Camera::Matrix(Shader& shader, const char* uniform, const char* uniform1)
{
	shader.setMat4(uniform, view);
    shader.setMat4(uniform1, projection);
}

void Camera::Inputs(GLFWwindow* window, float deltaTime)
{

    float cameraSpeed = speed * deltaTime; // Camera movement speed
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camPos += cameraSpeed * Direction;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camPos -= cameraSpeed * Direction;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camPos -= glm::normalize(glm::cross(Direction, camUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camPos += glm::normalize(glm::cross(Direction, camUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camPos += camUp * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        camPos -= camUp * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
        FOV = 10.0f;
    else
        FOV = normalFOV;
    // Mouse rotation for camera
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
    {
        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);
        // Initialize last mouse position if cursor was normal
        if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_NORMAL)
        {
            lastX = mouseX;
            lastY = mouseY;
        }
        // Disable cursor for camera control
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        // Calculate mouse movement offsets
        float offsetX = (float)(mouseY - lastY) * sensitivity;
        float offsetY = (float)(mouseX - lastX) * sensitivity;

        glm::vec3 newDirection = glm::rotate(Direction, glm::radians(offsetX), glm::cross(camUp, Direction));
        if (abs(glm::angle(newDirection, camUp) - glm::radians(90.0f)) <= glm::radians(85.0f))
        {
            Direction = newDirection;
        }
        Direction = glm::rotate(Direction, glm::radians(-offsetY), camUp);
        // Update last mouse position
        lastX = mouseX;
        lastY = mouseY;
    }
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
    {
        // Re-enable cursor when mouse button is released
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}