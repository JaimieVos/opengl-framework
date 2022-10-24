#pragma once

#include <assimp/scene.h>
#include <vector>
#include <string>

#include "shader.h"
#include "mesh.h"

class Model
{
public:
	Model(const std::string& path);
	
	void draw(const Shader& shader) const;

private:
	std::vector<Mesh> m_Meshes;
	std::vector<Texture> m_TexturesLoaded;

	std::string m_Directory;
	
	unsigned int textureCount = 0;

private:
	std::vector<Texture> loadMaterialTextures(const aiMaterial* material, const aiTextureType type, const ImageType imageType);
};