#pragma once
#ifndef TEXTUREHEADER
#define TEXTUREHEADER
#include <string>
#include "GL/freeglut.h"
#include <map>

using std::string;

class Texture
{
private:
	std::map<int, GLuint> textureIds;
	unsigned char* data = nullptr;
public:
	Texture(const string &filename);
	~Texture();
	void Bind();

	int width; 
	int height;
};

#endif
