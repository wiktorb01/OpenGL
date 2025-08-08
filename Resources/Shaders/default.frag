#version 330 core
// Output color of the fragment
out vec4 FragColor;
  
// Input color from vertex shader (not used in this fragment shader)
in vec3 ourColor;
// Input texture coordinates from vertex shader
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

// Texture samplers for two textures
uniform sampler2D texture0;
uniform sampler2D texture1;
// Uniform controlling the mix ratio between the two textures
uniform float miks; 
uniform vec3 lightColor;
uniform vec3 lightPos;



void main()
{
    float ambient = 0.2f;
    vec3 norm = normalize(Normal);
    vec3 lightDirection = normalize(lightPos - FragPos);
    float diffuse = max(dot(norm, lightDirection), 0.0f);
    vec3 result = (diffuse + ambient) * lightColor;
    // Sample both textures and blend them using the 'miks' value.
    // The second texture is mirrored horizontally by using -TexCoord.x.
    FragColor = mix(texture(texture0, TexCoord), texture(texture1, vec2(-TexCoord.x, TexCoord.y)), miks) * vec4(result, 1.0f);  
}