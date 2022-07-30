#pragma once

enum ImageFormat
{
	PNG,
	JPG
};

enum ImageType
{
	DIFFUSE,
	SPECULAR
};

const char* imageTypeToString(const ImageType imageType);

class Texture
{
public:
	Texture(const char* path, const ImageType imageType, const ImageFormat imageFormat, const unsigned int textureUnit);

	void bind() const;
	void unbind() const;
	
	const ImageType getImageType() const;

private:
	unsigned int m_Id;
	unsigned int m_TextureUnit;
	const ImageType m_ImageType;
};