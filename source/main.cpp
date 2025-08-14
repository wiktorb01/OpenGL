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

// Materials - Ambient components (RGB)
glm::vec3 materialAmbient[] = {
    glm::vec3(0.0215f, 0.1745f, 0.0215f),      // emerald
    glm::vec3(0.135f, 0.2225f, 0.1575f),       // jade
    glm::vec3(0.05375f, 0.05f, 0.06625f),      // obsidian
    glm::vec3(0.25f, 0.20725f, 0.20725f),      // pearl
    glm::vec3(0.1745f, 0.01175f, 0.01175f),    // ruby
    glm::vec3(0.1f, 0.18725f, 0.1745f),        // turquoise
    glm::vec3(0.329412f, 0.223529f, 0.027451f), // brass
    glm::vec3(0.2125f, 0.1275f, 0.054f),       // bronze
    glm::vec3(0.25f, 0.25f, 0.25f),            // chrome
    glm::vec3(0.19125f, 0.0735f, 0.0225f)      // copper
};

// Materials - Diffuse components (RGB)
glm::vec3 materialDiffuse[] = {
    glm::vec3(0.07568f, 0.61424f, 0.07568f),    // emerald
    glm::vec3(0.54f, 0.89f, 0.63f),             // jade
    glm::vec3(0.18275f, 0.17f, 0.22525f),       // obsidian
    glm::vec3(1.0f, 0.829f, 0.829f),            // pearl
    glm::vec3(0.61424f, 0.04136f, 0.04136f),    // ruby
    glm::vec3(0.396f, 0.74151f, 0.69102f),      // turquoise
    glm::vec3(0.780392f, 0.568627f, 0.113725f), // brass
    glm::vec3(0.714f, 0.4284f, 0.18144f),       // bronze
    glm::vec3(0.4f, 0.4f, 0.4f),                // chrome
    glm::vec3(0.7038f, 0.27048f, 0.0828f)       // copper
};

// Materials - Specular components (RGB)
glm::vec3 materialSpecular[] = {
    glm::vec3(0.633f, 0.727811f, 0.633f),       // emerald
    glm::vec3(0.316228f, 0.316228f, 0.316228f), // jade
    glm::vec3(0.332741f, 0.328634f, 0.346435f), // obsidian
    glm::vec3(0.296648f, 0.296648f, 0.296648f), // pearl
    glm::vec3(0.727811f, 0.626959f, 0.626959f), // ruby
    glm::vec3(0.297254f, 0.30829f, 0.306678f),  // turquoise
    glm::vec3(0.992157f, 0.941176f, 0.807843f), // brass
    glm::vec3(0.393548f, 0.271906f, 0.166721f), // bronze
    glm::vec3(0.774597f, 0.774597f, 0.774597f), // chrome
    glm::vec3(0.256777f, 0.137622f, 0.086014f)  // copper
};

// Materials - Shininess values
float materialShininess[] = {
    76.8f,        // emerald (0.6 * 128)
    12.8f,        // jade (0.1 * 128)
    38.4f,        // obsidian (0.3 * 128)
    11.264f,      // pearl (0.088 * 128)
    76.8f,        // ruby (0.6 * 128)
    12.8f,        // turquoise (0.1 * 128)
    27.8974f,     // brass (0.21794872 * 128)
    25.6f,        // bronze (0.2 * 128)
    76.8f,        // chrome (0.6 * 128)
    12.8f         // copper (0.1 * 128)
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
    Texture texture0("./Resources/Textures/container2.png", 0);
    Texture texture1("./Resources/Textures/container2_specular.png", 1);
    shader.setInt("material.diffuse", 0);
    shader.setInt("material.specular", 1);
    glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, -2.0f);


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
    
    

    Camera camera(SCR_WIDTH, SCR_HEIGHT, 60.0f, glm::vec3(0.0f, 0.0f, 3.0f));

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

        shader.Activate();
        // light properties
        shader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
        shader.setVec3("light.diffuse", 0.8f, 0.8f, 0.8f);
        shader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
        shader.setVec3("light.position", 0.0f, 0.0f, -0.1f);
        shader.setVec3("light.direction", 0.0f, 0.0f, -1.0f);
        shader.setFloat("light.innerCone", 0.91f);
        shader.setFloat("light.outerCone", 0.82f);
        shader.setFloat("light.constant", 1.0f);
        shader.setFloat("light.linear", 0.045f);
        shader.setFloat("light.quadratic", 0.0075f);

        // material properties
        shader.setFloat("material.shininess", 64.0f);
        camera.Matrix(shader, "view", "projection");

        VAO1.Bind();
        texture0.Bind();
        texture1.Bind();
        // Draw 10 cubes with different positions and rotations
        for (unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            shader.setMat4("model", model);
            // Draw the cube using glDrawArrays
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // Light
        lightShader.Activate();
        lightVAO.Bind();

        glm::mat4 lightModel = glm::mat4(1.0f);
        lightModel = glm::translate(lightModel, lightPos);
        lightShader.setMat4("lightModel", lightModel);

        camera.Matrix(lightShader, "view", "projection");
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
    
}


// Callback for window resize to update viewport and window size variables
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    SCR_HEIGHT = height;
    SCR_WIDTH = width;
}