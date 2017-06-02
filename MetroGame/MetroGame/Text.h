#pragma once
#include "Font.h"
class Text
{
	string text;
	float x, y;
	Font* font;

public:
	Text(float x, float y, Font* font, string text);
	~Text();
	float getX();
	float getY();
	void setX(float);
	void setY(float);
	string getText();
	Font* getFont();
};
	
