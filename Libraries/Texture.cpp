// Libraries\src\Texture.cpp
#include "Texture.h"

Texture::Texture(const char* path, GLuint slot)
{

    int width, height, nrChannels;
    // Flip image vertically to match OpenGL's coordinate system
    stbi_set_flip_vertically_on_load(true);
    // Load image data from file
    unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
    // Generate texture object
    glGenTextures(1, &ID);
    // Activate texture slot
    glActiveTexture(GL_TEXTURE0 + slot);
    unit = slot;
    // Bind texture
    glBindTexture(GL_TEXTURE_2D, ID);

    // Set texture wrapping and filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Upload image data to GPU and generate mipmaps
    if (nrChannels == 4) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    }
    else if (nrChannels == 3) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    }
    else if (nrChannels == 1) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, data);
    }
    else {
        throw std::runtime_error("Unsupported number of channels in texture image");
    }


    glGenerateMipmap(GL_TEXTURE_2D);

    // Free image memory
    stbi_image_free(data);
    // Unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::useTex(Shader& shader, const char* uniform)
{
    // Set the texture uniform value
    shader.setInt(uniform, unit);
}

void Texture::Bind()
{
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::Unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Delete()
{
    glDeleteTextures(1, &ID);
}