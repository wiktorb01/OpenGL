#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<Tex>& textures)
{
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;

    setupMesh();
}

void Mesh::setupMesh()
{
    VAO.Bind();
    VBO VBO(vertices);
    EBO EBO(indices);
    VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
    VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    VAO.LinkAttrib(VBO, 2, 2, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
    VAO.Unbind();
    VBO.Unbind();
    EBO.Unbind();
}

void Mesh::Draw(Shader& shader)
{
    unsigned int numDiff = 1;
    unsigned int numSpec = 1;
    for (unsigned int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        std::string number = "";
        std::string name = textures[i].type;
        if (name == "texture_diffuse")
            number = std::to_string(numDiff++);
        if (name == "texture_specular")
            number = std::to_string(numSpec++);
        // now set the sampler to the correct texture unit
        glUniform1i(glGetUniformLocation(shader.ID, (name + number).c_str()), i);
        // and finally bind the texture
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }

    // Draw
    VAO.Bind();
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    VAO.Unbind();


    glActiveTexture(GL_TEXTURE0);
}
