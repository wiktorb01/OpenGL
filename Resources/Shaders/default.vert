#version 330 core
// Vertex attribute: position (location = 0)
layout (location = 0) in vec3 aPos;
// Vertex attribute: color (location = 1)
layout (location = 1) in vec3 aColor;
// Vertex attribute: texture coordinates (location = 2)
layout (location = 2) in vec2 aTexCoord;

// Output color to fragment shader
out vec3 ourColor;
// Output texture coordinates to fragment shader
out vec2 TexCoord;

// Transformation matrices provided by the application
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    // Compute the final vertex position in clip space
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    // Pass color to fragment shader
    ourColor = aColor;
    // Pass texture coordinates to fragment shader
    TexCoord = aTexCoord;
}