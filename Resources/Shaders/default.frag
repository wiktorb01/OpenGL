#version 330 core
struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};
struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;
uniform Light light;

// Output color of the fragment
out vec4 FragColor;
  
// Input color from vertex shader (not used in this fragment shader)
in vec3 ourColor;
// Input texture coordinates from vertex shader
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
in vec3 lightPos;

// Texture samplers for two textures
uniform sampler2D texture0;
uniform sampler2D texture1;
// Uniform controlling the mix ratio between the two textures
uniform float miks; 
uniform vec3 lightColor;



void main()
{
    vec3 ambient = light.ambient * lightColor * material.ambient;

    vec3 norm = normalize(Normal);
    vec3 lightDirection = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDirection), 0.0f);
    vec3 diffuse = light.diffuse * lightColor * (diff * material.diffuse);


    vec3 viewDir = normalize(-FragPos);
    vec3 reflectDir = reflect(-lightDirection, norm);
    float spec = pow(max(dot(viewDir,reflectDir),0.0f), material.shininess);
    vec3 specular = light.specular * lightColor * (spec * material.specular);

    
    vec3 result = diffuse + ambient + specular;
    // Sample both textures and blend them using the 'miks' value.
    // The second texture is mirrored horizontally by using -TexCoord.x.
    // mix(texture(texture0, TexCoord), texture(texture1, vec2(-TexCoord.x, TexCoord.y)), miks) * 
    FragColor = vec4(result, 1.0f);  
}