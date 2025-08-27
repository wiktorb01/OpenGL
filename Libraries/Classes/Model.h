#pragma once
#include <Mesh.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <stb/stb_image.h>

class Model
{
public:
	std::vector<Tex> textures_loaded;

	Model(const char* path)
	{
		loadModel(path);
	}
	void Draw(Shader& shader);
private:
	std::vector<Mesh> meshes;
	std::string directory;

	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Tex> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};
