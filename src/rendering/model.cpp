#include "model.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include "util/logger.h"

Model::Model(const std::string& path)
{	
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenNormals);

	// Check if the model is loaded correctly
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		logger::error("Failed to load model: " + std::string(path));
		
		return;
	}

	m_Directory = path.substr(0, path.find_last_of('/'));

	// Loop through all the meshes
	for (unsigned int i = 0; i < scene->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[i];
		
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<Texture> textures;
		
		// Vertices
		for (unsigned int j = 0; j < mesh->mNumVertices; j++)
		{
			Vertex vertex;
			
			vertex.m_Position = glm::vec3(mesh->mVertices[j].x, mesh->mVertices[j].y, mesh->mVertices[j].z);
			vertex.m_Normal = glm::vec3(mesh->mNormals[j].x, mesh->mNormals[j].y, mesh->mNormals[j].z);

			if (mesh->mTextureCoords[0])
				vertex.m_TexCoords = glm::vec2(mesh->mTextureCoords[0][j].x, mesh->mTextureCoords[0][j].y);
			else
				vertex.m_TexCoords = glm::vec2(0.0f, 0.0f);

			vertices.push_back(vertex);
		}

		// Indices
		for (unsigned int j = 0; j < mesh->mNumFaces; j++)
		{
			aiFace face = mesh->mFaces[j];
			
			for (unsigned int k = 0; k < face.mNumIndices; k++)
			{
				indices.push_back(face.mIndices[k]);
			}
		}

		// Textures
		if (mesh->mMaterialIndex >= 0)
		{
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
			
			// Diffuse textures
			std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, ImageType::DIFFUSE);
			for (unsigned int j = 0; j < diffuseMaps.size(); j++)
				textures.push_back(diffuseMaps[j]);
			
			// Specular textures
			std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, ImageType::SPECULAR);
			for (unsigned int j = 0; j < specularMaps.size(); j++)
				textures.push_back(specularMaps[j]);
		}
		
		m_Meshes.push_back(Mesh(vertices, indices, textures));
	}
}

void Model::draw(const Shader& shader) const
{
	for (unsigned int i = 0; i < m_Meshes.size(); i++)
		m_Meshes[i].draw(shader);
}

std::vector<Texture> Model::loadMaterialTextures(const aiMaterial* material, const aiTextureType type, const ImageType imageType)
{
	std::vector<Texture> textures;

	for (unsigned int i = 0; i < material->GetTextureCount(type); i++)
	{
		aiString str;
		material->GetTexture(type, i, &str);
		
		bool skip = false;
		for (unsigned int j = 0; j < m_TexturesLoaded.size(); j++)
		{
			if (textures[j].m_Path == str.C_Str())
			{
				textures.push_back(m_TexturesLoaded[j]);
				skip = true;
				break;
			}
		}
		
		if (!skip)
		{
			std::string texturePath = m_Directory + "/" + str.C_Str();
			Texture texture(texturePath.c_str(), imageType, textureCount++);
			texture.m_Path = str.C_Str();

			textures.push_back(texture);
		}
	}

	return textures;
}