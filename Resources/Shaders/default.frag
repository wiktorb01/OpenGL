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
uniform vec3 viewPos;



void main()
{
    float ambient = 0.2f;

    vec3 norm = normalize(Normal);
    vec3 lightDirection = normalize(lightPos - FragPos);
    float diffuse = max(dot(norm, lightDirection), 0.0f);


    float specularStrength = 0.5f;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDirection, norm);
    float specular = specularStrength * pow(max(dot(viewDir,reflectDir),0.0f), 8);

    
    vec3 result = (diffuse + ambient + specular) * lightColor;
    // Sample both textures and blend them using the 'miks' value.
    // The second texture is mirrored horizontally by using -TexCoord.x.
    FragColor = mix(texture(texture0, TexCoord), texture(texture1, vec2(-TexCoord.x, TexCoord.y)), miks) * vec4(result, 1.0f);  
}