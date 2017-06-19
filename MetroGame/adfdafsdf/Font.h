#pragma once
#include <string>
#include <GL/freeglut.h>
#include <map>

using std::string;
using std::map;

class Texture;

class Font
{
private:
	GLuint listBase;
	Texture* texture;
	struct Glyph
	{
		int id;
		int x;
		int y;
		int width;
		int height;
		int xoffset;
		int yoffset;
		int xadvance;
	};

	map<int, Glyph> glyphs;

public:
	Font(const string &source);
	void drawText(const string &text);
	void drawText(const string &text, int x, int y);
	int textLength(const string &text);
	~Font();
};

