#pragma once

#include<EBO.h>
#include<VAO.h>
#include<Camera.h>

struct Tex {
	unsigned int id;
	std::string type;
	std::string path;
};

class Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Tex> textures;

	Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<Tex>& textures);
	void Draw(Shader& shader);

private:
	VAO VAO;

	void setupMesh();
};

