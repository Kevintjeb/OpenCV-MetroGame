#pragma once
#ifndef TEXTUREHEADER
#define TEXTUREHEADER
#include <string>
#include "GL/freeglut.h"

using std::string;

class Texture
{
private:
	GLuint textureId;
public:
	Texture(const string &filename);
	~Texture();
	void Bind();

	int width; 
	int height;
};

#endif
