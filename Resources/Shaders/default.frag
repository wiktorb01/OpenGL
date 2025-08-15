#version 330 core
struct Material {
    sampler2D diffuse;
    sampler2D specular;

    float shininess;
};
// Directional Light
struct DirLight {
    vec3 direction;
    bool isOn;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
// Flashlight
struct Flashlight {
    vec3 posOffset;
    vec3 direction;
    bool isOn;

    float innerCone;
    float outerCone;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};
// PointLight
struct PointLight {
    vec3 position;
    vec3 color;

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

// Uniforms
uniform Material material;
uniform Flashlight flash;
uniform DirLight sun;
uniform PointLight light[4];


vec3 flashlight(Flashlight light)
{
    if(!light.isOn) return vec3(0.0f);
    float distance = length(light.posOffset-FragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance + distance * distance * light.quadratic);
    
    vec3 lightDir = normalize(light.posOffset-FragPos);
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

vec3 sunlight(DirLight sun)
{
    if(sun.isOn)
    {
        vec3 ambient = sun.ambient * texture(material.diffuse, TexCoord).rgb;
        // diffuse
        vec3 lightDir = normalize(sun.direction);
        vec3 norm = normalize(Normal);
        float diff = max(dot(norm, lightDir), 0.0f);
        vec3 diffuse = sun.diffuse * diff * texture(material.diffuse, TexCoord).rgb;
        // specular
        vec3 viewDir = normalize(-FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        vec3 specular = sun.specular * spec * texture(material.specular, TexCoord).rgb;

        return ambient + diffuse + specular;
    }
    else
    {
        return vec3(0.0f);
    }
}

vec3 pointlight(PointLight light)
{   
    float distance = length(light.position - FragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance + distance * distance * light.quadratic);
    vec3 lightDir = normalize(light.position - FragPos);

    // ambient
    vec3 ambient = light.color * light.ambient * attenuation * texture(material.diffuse, TexCoord).rgb;
    // diffuse
    vec3 norm = normalize(Normal);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.color * light.diffuse * diff * attenuation * texture(material.diffuse, TexCoord).rgb;
    // specular
    vec3 viewDir = normalize(-FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = spec * light.color * light.specular * attenuation * texture(material.specular, TexCoord).rgb;
    //result
    vec3 result = ambient + diffuse + specular;

    return result;
}

void main()
{
    vec3 result = flashlight(flash) + sunlight(sun);
    for(int i =0; i<4; i++)
        result += pointlight(light[i]);
    FragColor = vec4(result, 1.0f);  
}