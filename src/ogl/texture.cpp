#include "texture.h"

#include <GL/glew.h>
#include <stb_image.h>

#include "util/logger.h"

Texture::Texture(const char* path, const ImageType imageType, const unsigned int textureUnit)
	: m_ImageType(imageType), m_TextureUnit(textureUnit)
{
	glGenTextures(1, &m_Id);
	glActiveTexture(GL_TEXTURE0 + m_TextureUnit);
	glBindTexture(GL_TEXTURE_2D, m_Id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
	if (data)
	{
		GLenum format;
		if (nrChannels == 1)
			format = GL_RED;
		else if (nrChannels == 3)
			format = GL_RGB;
		else if (nrChannels == 4)
			format = GL_RGBA;
		else
		{
			logger::error("Failed to load texture: " + std::string(path));
			stbi_image_free(data);
			return;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		logger::error("Failed to load texture: " + std::string(path));
	}

	stbi_image_free(data);
}

void Texture::bind() const
{
	glActiveTexture(GL_TEXTURE0 + m_TextureUnit);
	glBindTexture(GL_TEXTURE_2D, m_Id);
}

void Texture::unbind() const
{
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

const ImageType Texture::getImageType() const
{
	return m_ImageType;
}

const char* imageTypeToString(const ImageType imageType)
{
	switch (imageType)
	{
	case ImageType::DIFFUSE:
		return "diffuse";
		break;
	case ImageType::SPECULAR:
		return "specular";
		break;
	default:
		throw std::runtime_error("Invalid image type");
	}
}
