#pragma once

#include "Vect.h"
#include <list>
#include <memory>

namespace mg_gameLogic
{
	class Line
	{
	public:
		float *distances;
		Vec2f *positions;
		int length;

		Line(std::list<Vec2f> line);
		int getIndexByPosition(float position);
	};
}