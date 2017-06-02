#include "Text.h"



Text::~Text()
{
}

Text::Text(float x, float y, Font * font, string text)
{
	this->x = x;
	this->y = y;
	this->font = font;
	this->text = text;
}

float Text::getX()
{
	return x;
}

float Text::getY()
{
	return y;
}

void Text::setX(float x)
{
	this->x = x;
}

void Text::setY(float y)
{
	this->y = y;
}

string Text::getText()
{
	return text;
}

Font* Text::getFont() {
	return font;
}
