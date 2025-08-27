// main.cpp - Entry point for the OpenGL application
// This file sets up the OpenGL context, loads shaders, textures, and handles rendering and input.
#include <iostream>
#include <map>

#include "Model.h"
#include "Camera.h"

// Callback function for window resize events
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
// Handles keyboard and mouse input
void processInput(GLFWwindow* window);
unsigned int loadTexture(const char* path, GLenum texture_wrap_s = GL_REPEAT, GLenum texture_wrap_t = GL_REPEAT);


// Window settings
unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;

// Camera and view settings 
float deltaTime = 0.0f;
float lastFrame = 0.0f;
// lightning
bool firstF = 1, isF = 0;

float cubeVertices[] = {
    // positions          // texture Coords
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};
float planeVertices[] = {
    // positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
     5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
    -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
    -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

     5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
    -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
     5.0f, -0.5f, -5.0f,  2.0f, 2.0f
};
float grassVertices[] = {
    // positions         // texture Coords 
	1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	1.0f,  1.0f,  0.0f,  1.0f, 1.0f,
	0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
	0.0f,  0.0f,  0.0f,  0.0f, 0.0f
};
GLuint grassIndices[] = {
    0, 1, 2,
    0, 2, 3
};

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
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // Create and activate shader program
    Shader shader("./Resources/Shaders/default.vert", "./Resources/Shaders/default.frag");
    Shader singleColorShader("./Resources/Shaders/default.vert", "./Resources/Shaders/singleColor.frag");

    // Cube
    VAO VAO1;
    VAO1.Bind();
    VBO VBO1(cubeVertices, sizeof(cubeVertices));
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO1.Unbind();
    VBO1.Unbind();
    // Plane
    VAO VAO2;
    VAO2.Bind();
    VBO VBO2(planeVertices, sizeof(planeVertices));
    VAO2.LinkAttrib(VBO2, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
    VAO2.LinkAttrib(VBO2, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO2.Unbind();
    VBO2.Unbind();
    // Grass
    std::vector<glm::vec3> windows;
    windows.push_back(glm::vec3(-1.5f, 0.0f, -0.48f));
    windows.push_back(glm::vec3(1.5f, 0.0f, 0.51f));
    windows.push_back(glm::vec3(0.0f, 0.0f, 0.7f));
    windows.push_back(glm::vec3(-0.3f, 0.0f, -2.3f));
    windows.push_back(glm::vec3(0.5f, 0.0f, -0.6f));
    VAO grassVAO;
    grassVAO.Bind();
    VBO grassVBO(grassVertices, sizeof(grassVertices));
    EBO grassEBO(grassIndices, sizeof(grassIndices));
    grassVAO.LinkAttrib(grassVBO, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
    grassVAO.LinkAttrib(grassVBO, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    grassVAO.Unbind();
    grassEBO.Unbind();
    grassVBO.Unbind();
    // textures
    unsigned int cubeTexture = loadTexture("./Resources/Textures/marble.jpg");
    unsigned int floorTexture = loadTexture("./Resources/Textures/metal.jpg");
    unsigned int grassTexture = loadTexture("./Resources/Textures/blending_transparent_window.png", GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
    shader.Activate();
    shader.setInt("texture1", 0);


    Camera camera(SCR_WIDTH, SCR_HEIGHT, 60.0f, glm::vec3(0.0f, 0.0f, 3.0f));
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
        camera.updateMatrix(0.1f, 100.0f, SCR_WIDTH, SCR_HEIGHT);

        // Clear the color and depth buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        // Drawing commands
        shader.Activate();
        camera.Matrix(shader, "view", "projection");
        glm::mat4 model;
        // Floor 
        glStencilMask(0x00); // make sure we don't update the stencil buffer while drawing the floor
        VAO2.Bind();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, floorTexture);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -0.001f, 0.0f));
        shader.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        VAO2.Unbind();
        
        // Cubes 
        VAO1.Bind();
        glBindTexture(GL_TEXTURE_2D, cubeTexture);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f)); // translate it down so it's at the center of the scene
        shader.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
        shader.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        VAO1.Unbind();
        // Grass
        grassVAO.Bind();
        glBindTexture(GL_TEXTURE_2D, grassTexture);
        std::map<float, glm::vec3> sorted;
        for (unsigned int i = 0; i < windows.size(); i++)
        {
            float distance = glm::length(camera.camPos - windows[i]);
            sorted[distance] = windows[i];
        }
        for (std::map<float, glm::vec3>::reverse_iterator it = sorted.rbegin(); it != sorted.rend(); ++it)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(it->second.x, it->second.y - 0.5f, it->second.z));
            shader.setMat4("model", model);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }
        grassVAO.Unbind();

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

// Texture loading utility function
unsigned int loadTexture(const char* path, GLenum texture_wrap_s, GLenum texture_wrap_t)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrChannels;
    unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (data)
    {
        GLenum format;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;
        else 
            throw std::runtime_error("Unsupported number of channels in texture image");
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texture_wrap_s);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texture_wrap_t);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
	return textureID;
}