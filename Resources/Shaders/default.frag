#version 330 core
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
out vec4 FragColor;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform Flashlight flash;

vec3 flashlight(Flashlight light)
{
    float distance = length(FragPos);
    float attenuation = 1 / (light.constant + light.linear * distance + distance * distance * light.quadratic);

    vec3 lightDir = normalize(light.posOffset-FragPos);
    float theta = dot(normalize(-light.direction), lightDir);

    vec3 ambient = attenuation * light.ambient * texture(texture_diffuse1, TexCoords).rgb;

    if(light.isOn && theta >= light.outerCone)
    {
        float intensity = clamp((theta - light.outerCone)/(light.innerCone - light.outerCone), 0.0f, 1.0f);
        // diffuse lightning
        vec3 norm = normalize(Normal);
        float diff = max(dot(norm, lightDir), 0.0f);
        vec3 diffuse = intensity * attenuation * diff * texture(texture_diffuse1, TexCoords).rgb;
        // specular lightning
        vec3 viewDir = lightDir;
        vec3 reflectDir = reflect( -lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32);
        vec3 specular = spec * intensity * attenuation * texture(texture_specular1, TexCoords).rgb;

        return ambient + specular + diffuse;
    }
    else
        return ambient;
}

void main()
{    
    FragColor = texture(texture_diffuse1, TexCoords) * vec4(flashlight(flash), 1.0);
}