#version 330 core
// Vertex attribute: position (location = 0)
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
// Vertex attribute: color (location = 2)
layout (location = 2) in vec3 aColor;
// Vertex attribute: texture coordinates (location = 3)
layout (location = 3) in vec2 aTexCoord;

// Output color to fragment shader
out vec3 ourColor;
// Output texture coordinates to fragment shader
out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;
out vec3 lightPos;

// Transformation matrices provided by the application
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 lightPosition;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    FragPos = vec3(view * model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(view * model))) * aNormal;
    lightPos = vec3(view * vec4(lightPosition, 1.0)); // Transform world-space light position to view-space light position

    ourColor = aColor;
    TexCoord = aTexCoord;
}