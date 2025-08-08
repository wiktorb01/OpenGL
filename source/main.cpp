// main.cpp - Entry point for the OpenGL application
// This file sets up the OpenGL context, loads shaders, textures, and handles rendering and input.


#include <iostream>

#include "VBO.h"
#include "VAO.h"
#include "EBO.h"
#include "Shader.h"
#include "Texture.h"
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
float mix = 0.5f; // Texture mix value

// Vertex data for a cube (positions, colors, texture coordinates)
float vertices[] = {
    -0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   0.0f, 0.0f, 0.0f,   0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   0.0f, 0.0f, 0.0f,   1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   0.0f, 0.0f, 0.0f,   1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   0.0f, 0.0f, 0.0f,   1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   0.0f, 0.0f, 0.0f,   0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   0.0f, 0.0f, 0.0f,   0.0f, 0.0f,
                                                                   
    -0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   0.0f, 0.0f, 0.0f,   0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   0.0f, 0.0f, 0.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   0.0f, 0.0f, 0.0f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   0.0f, 0.0f, 0.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   0.0f, 0.0f, 0.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   0.0f, 0.0f, 0.0f,   0.0f, 0.0f,
                                                                   
    -0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,   0.0f, 0.0f, 0.0f,   1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,   0.0f, 0.0f, 0.0f,   1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,   0.0f, 0.0f, 0.0f,   0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,   0.0f, 0.0f, 0.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,   0.0f, 0.0f, 0.0f,   0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,   0.0f, 0.0f, 0.0f,   1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f,   0.0f, 0.0f, 0.0f,   1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,   1.0f,  0.0f,  0.0f,   0.0f, 0.0f, 0.0f,   1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,   0.0f, 0.0f, 0.0f,   0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,   0.0f, 0.0f, 0.0f,   0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,   1.0f,  0.0f,  0.0f,   0.0f, 0.0f, 0.0f,   0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f,   0.0f, 0.0f, 0.0f,   1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,   0.0f, 0.0f, 0.0f,   0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,   0.0f, 0.0f, 0.0f,   1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,   0.0f, 0.0f, 0.0f,   1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,   0.0f, 0.0f, 0.0f,   1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,   0.0f, 0.0f, 0.0f,   0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,   0.0f, 0.0f, 0.0f,   0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,   0.0f, 0.0f, 0.0f,   0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,   0.0f, 0.0f, 0.0f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,   0.0f, 0.0f, 0.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,   0.0f, 0.0f, 0.0f,   1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,   0.0f, 0.0f, 0.0f,   0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,   0.0f, 0.0f, 0.0f,   0.0f, 1.0f
};

// Positions for multiple cubes in the scene
glm::vec3 cubePositions[] = {
    glm::vec3(0.0f,  0.0f,  0.0f),
    glm::vec3(2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(1.5f,  2.0f, -2.5f),
    glm::vec3(1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
};

float lightVertices[] =
{
     0.1f,  0.1f, -0.1f,
     0.1f,  0.1f,  0.1f,
     0.1f, -0.1f, -0.1f,
     0.1f, -0.1f,  0.1f,
    -0.1f,  0.1f, -0.1f,
    -0.1f,  0.1f,  0.1f,
    -0.1f, -0.1f, -0.1f,
    -0.1f, -0.1f,  0.1f
};

GLuint lightIndices[] =
{
    0,1,2, 1,2,3,
    1,5,7, 1,7,3,
    4,5,6, 5,6,7,
    0,4,6, 0,6,2,
    0,1,4, 1,4,5,
    2,3,6, 3,6,7
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

    // Cubes
    // Create and activate shader program
    Shader shader("./Resources/Shaders/default.vert", "./Resources/Shaders/default.frag");
    shader.Activate();
    // Load and bind textures
    Texture texture0("./Resources/Textures/container.jpg", 0);
    Texture texture1("./Resources/Textures/awesomeface.png", 1);
    texture0.useTex(shader, "texture0");
    texture1.useTex(shader, "texture1");


    // Create VAO and VBO, and link vertex attributes
    VAO VAO1;
    VAO1.Bind();
    VBO VBO1(vertices, sizeof(vertices));
    //EBO EBO(indices, sizeof(indices)); // EBO is commented out, not used
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0); // Position attribute
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float))); // Normals
    VAO1.LinkAttrib(VBO1, 2, 3, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float))); // Color attribute
    VAO1.LinkAttrib(VBO1, 3, 2, GL_FLOAT, 11 * sizeof(float), (void*)(9 * sizeof(float))); // Texture coordinate attribute
    VAO1.Unbind();
    VBO1.Unbind();
    //EBO.Unbind();

    // Light
    Shader lightShader("./Resources/Shaders/light.vert", "./Resources/Shaders/light.frag");
    VAO lightVAO;
    lightVAO.Bind();
    VBO lightVBO(lightVertices, sizeof(lightVertices));
    EBO lightEBO(lightIndices, sizeof(lightIndices));
    lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
    lightVAO.Unbind();
    lightVBO.Unbind();
    lightEBO.Unbind();
    lightShader.Activate();
   
    
    
    glm::vec3 lightColor(1.0f, 1.0f, 1.0f);

    Camera camera(SCR_WIDTH, SCR_HEIGHT, 60.0f, glm::vec3(0.0f, 0.0f, 3.0f));

    // Enable depth testing for 3D rendering
    glEnable(GL_DEPTH_TEST);
    // Render loop
    while (!glfwWindowShouldClose(window))
    {
        // Calculate frame timing
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        // Handle input
        processInput(window);
        camera.Inputs(window, deltaTime);

        // Clear the color and depth buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);


        glm::vec3 lightPos = glm::vec3(0.0f, sin(currentFrame/4) * 4.0f, -2.0f);
        glm::mat4 lightModel = glm::mat4(1.0f);
        lightModel = glm::translate(lightModel, lightPos);


        camera.updateMatrix(0.1f, 100.0f);

        shader.Activate();
        camera.Matrix(shader, "camMatrix");
        VAO1.Bind();
        texture0.Bind();
        texture1.Bind();
        shader.setFloat("miks", mix);
        shader.setVec3("lightColor", lightColor);
        shader.setVec3("lightPos", lightPos);
        shader.setVec3("viewPos", camera.camPos);
        // Draw 10 cubes with different positions and rotations
        for (unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = i * 20.0f;
            angle += (float)glfwGetTime() * 25.0f;
            model = glm::rotate(model,  glm::radians(angle), glm::normalize(glm::vec3((i+1)*1.0f, (i + 1) * 0.3f, (i + 1) * 0.5f)));
            shader.setMat4("model", model);
            // Draw the cube using glDrawArrays
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // Light
        lightShader.Activate();
        lightVAO.Bind();
        lightShader.setMat4("lightModel", lightModel);
        lightShader.setVec3("lightColor", lightColor);
        camera.Matrix(lightShader, "camMatrix");
        glDrawElements(GL_TRIANGLES, sizeof(lightIndices)/sizeof(unsigned int), GL_UNSIGNED_INT, 0);
        // Swap buffers and poll IO events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup: delete VAO and VBO
    VAO1.Delete();
    VBO1.Delete();

    // Terminate GLFW and release resources
    glfwTerminate();
    return 0;
}

// Handles keyboard and mouse input for camera movement and texture mixing
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        if(mix>0.0) mix -= 0.01f;
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        if(mix<1.0)mix += 0.01f;
    
}


// Callback for window resize to update viewport and window size variables
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    SCR_HEIGHT = height;
    SCR_WIDTH = width;
}