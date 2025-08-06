#version 330 core
// Output color of the fragment
out vec4 FragColor;
  
// Input color from vertex shader (not used in this fragment shader)
in vec3 ourColor;
// Input texture coordinates from vertex shader
in vec2 TexCoord;

// Texture samplers for two textures
uniform sampler2D texture0;
uniform sampler2D texture1;
// Uniform controlling the mix ratio between the two textures
uniform float miks; 

void main()
{
    // Sample both textures and blend them using the 'miks' value.
    // The second texture is mirrored horizontally by using -TexCoord.x.
    FragColor = mix(texture(texture0, TexCoord), texture(texture1, vec2(-TexCoord.x, TexCoord.y)), miks);  
}