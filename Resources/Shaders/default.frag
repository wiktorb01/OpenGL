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
    sampler2D emission;
    float shininess;
};
struct Light {
    vec3 direction;
    vec3 position;
    float innerCone;
    float outerCone;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};


// Output color of the fragment
out vec4 FragColor;
  
// Input color from vertex shader (not used in this fragment shader)
in vec3 ourColor;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
in vec3 lightPos;

uniform vec3 viewPos;
uniform MaterialTex material;
uniform Light light;

vec3 flashlight()
{
    float distance = length(light.position-FragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance + distance * distance * light.quadratic);
    
    vec3 lightDir = normalize(light.position-FragPos);
    float theta = dot(lightDir, normalize(-light.direction));

    if ( theta > light.outerCone )
    {
        float intensity = clamp( (theta - light.outerCone) / (light.innerCone - light.outerCone), 0.0f, 1.0f);
        // ambient
        vec3 ambient = light.ambient * attenuation * texture(material.diffuse, TexCoord).rgb;

        // diffuse
        vec3 norm = normalize(Normal);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = light.diffuse * diff * intensity * attenuation * texture(material.diffuse, TexCoord).rgb;
        
        // specular
        vec3 viewDir = normalize(-FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir,reflectDir),0.0f), material.shininess);
        vec3 specular = light.specular * spec * intensity * attenuation * texture(material.specular, TexCoord).rgb;

        return ambient + diffuse + specular;
    }
    else
    {  
        return light.ambient * attenuation * texture(material.diffuse, TexCoord).rgb;
    }
}
void main()
{
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoord).rgb;

    float distance = length(lightPos - FragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance + distance * distance * light.quadratic);

    vec3 norm = normalize(Normal);
    vec3 lightDirection = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDirection), 0.0f);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoord).rgb;


    vec3 viewDir = normalize(-FragPos);
    vec3 reflectDir = reflect(-lightDirection, norm);
    float spec = pow(max(dot(viewDir,reflectDir),0.0f), material.shininess);
    vec3 specular = light.specular * (spec * texture(material.specular, TexCoord).rgb);

    
    vec3 result = attenuation * (diffuse + ambient + specular);
    FragColor = vec4(flashlight(), 1.0f);  
}