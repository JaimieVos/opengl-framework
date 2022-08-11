#pragma once

#include <string>

enum ImageType
{
	DIFFUSE,
	SPECULAR
};

const char* imageTypeToString(const ImageType imageType);

class Texture
{
public:
	std::string m_Path;

public:
	Texture(const char* path, const ImageType imageType, const unsigned int textureUnit);

	void bind() const;
	void unbind() const;
	
	const ImageType getImageType() const;

private:
	unsigned int m_Id;
	unsigned int m_TextureUnit;
	const ImageType m_ImageType;
};