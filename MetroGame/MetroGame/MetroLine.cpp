#include "MetroLine.h"
#pragma once

mg_gameLogic::MetroLine::MetroLine(std::list<Vec2f> openCV)
{
		
}

mg_gameLogic::MetroLine::~MetroLine() {}






std::list<Vec2f> mg_gameLogic::MetroLine::filterData(std::list<Vec2f> data)
{
	std::list<Vec2f >  filtered;
	Vec2f previousVector;
	for (Vec2f vector : data)
	{
		if (compareVector(vector, previousVector)) {
			filtered.push_back(vector);
			//filtered.push_back(vector);
			previousVector = vector;
		}
	}
	return std::list<Vec2f>();
}

bool mg_gameLogic::MetroLine::compareVector(Vec2f v1, Vec2f v2)
{
	if (abs(v1.x - v2.x) > MARGINX || abs(v1.y - v2.y) > MARGINY)
	{
		return true;
	}
	return false;
}
