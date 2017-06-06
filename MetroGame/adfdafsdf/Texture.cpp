#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Texture.h"
#include <iostream>


Texture::Texture(const string &filename)
{
	int bpp2;

	stbi_set_flip_vertically_on_load(1);

	data = stbi_load(filename.c_str(), &width, &height, &bpp2, 4);
	if (!data)
		std::cout << stbi_failure_reason() << std::endl;
}

void Texture::Bind() {
	int window = glutGetWindow();
	if (textureIds.find(window) == textureIds.end())
	{
		GLuint textureId;
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
			data);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		textureIds[window] = textureId;
	}
	glBindTexture(GL_TEXTURE_2D, textureIds[window]);
}


Texture::~Texture()
{
//TODO
//	if(data)
//		stbi_image_free(data);
//	data = nullptr;
}
