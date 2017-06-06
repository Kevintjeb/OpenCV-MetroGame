#include "Font.h"
#include <GL/freeglut.h>
#include <fstream>
#include <algorithm>
#include <vector>
#include "Texture.h"
#include <iostream> 

/**
* Replaces a substring in a string
*/
static std::string replace(std::string str, const std::string &toReplace, const std::string &replacement)
{
	size_t index = 0;
	while (true)
	{
		index = str.find(toReplace, index);
		if (index == std::string::npos)
			break;
		str.replace(index, toReplace.length(), replacement);
		++index;
	}
	return str;
}

/**
* Splits a string into substrings, based on a seperator
*/
static std::vector<std::string> split(std::string str, const std::string &seperator)
{
	std::vector<std::string> ret;
	size_t index;
	while (true)
	{
		index = str.find(seperator);
		if (index == std::string::npos)
			break;
		ret.push_back(str.substr(0, index));
		str = str.substr(index + 1);
	}
	ret.push_back(str);
	return ret;
}

/**
* Turns a string to lowercase
*/
static inline std::string toLower(std::string data)
{
	std::transform(data.begin(), data.end(), data.begin(), ::tolower);
	return data;
}


/**
* Cleans up a line for processing
*/
static inline std::string cleanLine(std::string line)
{
	line = replace(line, "\t", " ");
	while (line.find("  ") != std::string::npos)
		line = replace(line, "  ", " ");
	if (line == "")
		return "";
	if (line[0] == ' ')
		line = line.substr(1);
	if (line == "")
		return "";
	if (line[line.length() - 1] == ' ')
		line = line.substr(0, line.length() - 1);
	return line;
}

int Font::textLength(const string &text) {
	int width = 0;
	for (size_t i = 0; i < text.size(); i++)
	{
		width += glyphs[text[i]].xadvance;
	}
	return width;
}

Font::Font(const string & source)
{
	std::ifstream input(source);
	if (!input.is_open())
		std::cout << "Could not open " << source << std::endl;
	listBase = glGenLists(256);
	while (!input.eof()) {
		string line;
		std::getline(input, line);
		line = cleanLine(line);
		auto segments = split(line, " ");
		if (segments[0] == "char") {
			Glyph glyph;
			for (int i = 1; i < segments.size(); i++)
			{
				auto param = split(segments[i], "=");
				if (param[0] == "id")		glyph.id = atoi(param[1].c_str());
				if (param[0] == "x")		glyph.x = atoi(param[1].c_str());
				if (param[0] == "y")		glyph.y = atoi(param[1].c_str());
				if (param[0] == "width")	glyph.width = atoi(param[1].c_str());
				if (param[0] == "height")	glyph.height = atoi(param[1].c_str());
				if (param[0] == "xoffset")	glyph.xoffset = atoi(param[1].c_str());
				if (param[0] == "yoffset")	glyph.yoffset = atoi(param[1].c_str());
				if (param[0] == "xadvance") glyph.xadvance = atoi(param[1].c_str());
			}
			glyphs[glyph.id] = glyph;
			glNewList(listBase + glyph.id, GL_COMPILE);
			glBegin(GL_QUADS);
			glTexCoord2f((glyph.x + 0) / (float)texture->width, 1-(glyph.y + 0) / (float)texture->height);
			glVertex2f(glyph.xoffset + 0,				glyph.yoffset + 0);

			glTexCoord2f((glyph.x + glyph.width) / (float)texture->width, 1 - (glyph.y + 0) / (float)texture->height);
			glVertex2f(glyph.xoffset + glyph.width,		glyph.yoffset + 0);

			glTexCoord2f((glyph.x + glyph.width) / (float)texture->width, 1 - (glyph.y + glyph.height) / (float)texture->height);
			glVertex2f(glyph.xoffset + glyph.width,		glyph.yoffset + glyph.height);

			glTexCoord2f((glyph.x + 0) / (float)texture->width, 1 - (glyph.y + glyph.height) / (float)texture->height);
			glVertex2f(glyph.xoffset + 0,				glyph.yoffset + glyph.height);

			glEnd();

			glTranslatef(glyph.xadvance, 0, 0);
			glEndList();

		}
		else if(segments[0] == "page")
		{
			string textArgument = "error";
			for (size_t i = 0; i < segments.size(); i++)
			{	
				auto params = split(segments[i], "=");
				if (params[0] == "file") {
					textArgument = params[1];
					textArgument = replace(textArgument, "\"", "");
				}
			}
			texture = new Texture(textArgument);
		}
	}
}

void Font::drawText(const string &text)
{
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	texture->Bind();
	glListBase(listBase);
	glCallLists(text.size(), GL_UNSIGNED_BYTE, text.c_str());
	glListBase(0);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}


void Font::drawText(const string &text, int x, int y)
{
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	texture->Bind();
	glPushMatrix();
	glListBase(listBase);
	glTranslatef(x, y, 1.0f);
	glCallLists(text.size(), GL_UNSIGNED_BYTE, text.c_str());
	glListBase(0);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}

Font::~Font()
{
}
