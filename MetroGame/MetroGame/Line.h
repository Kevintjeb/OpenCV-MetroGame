#pragma once

#include "Vect.h"
#include <list>
#include <memory>
#define MARGINX 5
#define MARGINY 5
namespace mg_gameLogic
{
	class Line
	{
	public:
		float *distances;
		Vec2f *positions;
		int length;
		
		Line() = delete;
		Line(std::list<Vec2f> line);
		std::list<Vec2f> filterData(std::list<Vec2f> data);
		bool compareVector(Vec2f v1, Vec2f v2);
		int getIndexByPosition(float position);
	};
}