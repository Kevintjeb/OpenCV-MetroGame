#pragma once

#include "Vect.h"
#include <list>
#include <memory>
#include <valarray>

namespace mg_gameLogic
{
	class Line
	{
	private:
		std::valarray<float> distances;
		std::valarray<Vec2f> positions;
	public:
		Line() = delete;
		Line(const Line&) = delete;
		explicit Line(std::list<Vec2f> line);
		~Line();

		std::size_t size() const;
		int getIndexByPosition(float position) const;
		const Vec2f& operator[](int i) const;
	};
}