#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Texture.h"

Texture::Texture(const string &filename)
{
	int bpp2;

	stbi_set_flip_vertically_on_load(1);

	unsigned char* imgData = stbi_load(filename.c_str(), &width, &height, &bpp2, 4);

	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);

	glTexImage2D(GL_TEXTURE_2D,
		0,
		GL_RGBA,
		width,
		height,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		imgData);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	stbi_image_free(imgData);
}

void Texture::Bind() {
	glBindTexture(GL_TEXTURE_2D, textureId);
}


Texture::~Texture()
{
}
