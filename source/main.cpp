// main.cpp - Entry point for the OpenGL application
// This file sets up the OpenGL context, loads shaders, textures, and handles rendering and input.
#include <iostream>

#include "Model.h"
#include "Camera.h"

// Callback function for window resize events
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
// Handles keyboard and mouse input
void processInput(GLFWwindow* window);

// Window settings
unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;

// Camera and view settings 
float deltaTime = 0.0f;
float lastFrame = 0.0f;
// lightning
bool firstF = 1, isF = 0;

int main()
{
    // Initialize GLFW and configure OpenGL context version
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Set callback functions for window resize and scroll
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Load OpenGL function pointers using GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    stbi_set_flip_vertically_on_load(true);
    // Create and activate shader program
    Shader shader("./Resources/Shaders/default.vert", "./Resources/Shaders/default.frag");

    // Lightning
    shader.Activate();
    // Flashlight
    shader.setVec3("flash.ambient", 0.2f, 0.2f, 0.2f);
    shader.setVec3("flash.diffuse", 0.9f, 0.9f, 0.9f);
    shader.setVec3("flash.specular", 1.0f, 1.0f, 1.0f);
    shader.setVec3("flash.posOffset", 0.0f, 0.0f, -0.1f);
    shader.setVec3("flash.direction", 0.0f, 0.0f, -1.0f);
    shader.setFloat("flash.innerCone", 0.91f);
    shader.setFloat("flash.outerCone", 0.82f);
    shader.setFloat("flash.constant", 1.0f);
    shader.setFloat("flash.linear", 0.045f);
    shader.setFloat("flash.quadratic", 0.0075f);

    Camera camera(SCR_WIDTH, SCR_HEIGHT, 60.0f, glm::vec3(0.0f, 0.0f, 3.0f));
    Model backpack("./Resources/Models/backpack/backpack.obj");
    // Enable depth testing for 3D rendering
    glEnable(GL_DEPTH_TEST);
    // Render loop
    while (!glfwWindowShouldClose(window))
    {
        // Calculate frame timing
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Handle input
        processInput(window);
        camera.Inputs(window, deltaTime);
        camera.updateMatrix(0.1f, 100.0f);

        // Clear the color and depth buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        // Backpack
        shader.Activate();
        camera.Matrix(shader, "view", "projection");
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
        shader.setMat4("model", model);
        // Lightning
        shader.setBool("flash.isOn", isF);

        backpack.Draw(shader);

        // Swap buffers and poll IO events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Terminate GLFW and release resources
    glfwTerminate();
    return 0;
}

// Handles keyboard and mouse input for camera movement and texture mixing
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS && firstF)
    {
        firstF = 0;
        isF = !isF;
    }
    else if(glfwGetKey(window, GLFW_KEY_F) == GLFW_RELEASE)
    {
        firstF = 1;
    }
}

// Callback for window resize to update viewport and window size variables
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    SCR_HEIGHT = height;
    SCR_WIDTH = width;
}