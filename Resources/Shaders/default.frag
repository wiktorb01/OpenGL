#version 330 core
struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};
struct MaterialTex {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};
struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};


// Output color of the fragment
out vec4 FragColor;
  
// Input color from vertex shader (not used in this fragment shader)
in vec3 ourColor;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
in vec3 lightPos;

uniform MaterialTex material;
uniform Light light;
uniform sampler2D texture0;



void main()
{
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoord).rgb;

    vec3 norm = normalize(Normal);
    vec3 lightDirection = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDirection), 0.0f);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoord).rgb;


    vec3 viewDir = normalize(-FragPos);
    vec3 reflectDir = reflect(-lightDirection, norm);
    float spec = pow(max(dot(viewDir,reflectDir),0.0f), material.shininess);
    vec3 specular = light.specular * (spec * texture(material.specular, TexCoord).rgb);

    
    vec3 result = diffuse + ambient + specular;
    FragColor = vec4(result, 1.0f);  
}