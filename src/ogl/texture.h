#pragma once

enum ImageType
{
	PNG,
	JPG
};

class Texture
{
public:
	Texture(const char* path, const ImageType imageType, const unsigned int textureUnit);

	void bind() const;
	void unbind() const;

private:
	unsigned int m_Id;
	unsigned int m_TextureUnit;
};