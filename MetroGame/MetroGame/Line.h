#pragma once

#include "Vect.h"
#include <list>
#include <memory>
#define MARGINX 0.8
#define MARGINY 0.8
#include <valarray>

namespace mg_gameLogic
{
	std::list<Vec2f> filterData(std::list<Vec2f> data);
	bool compareVector(Vec2f v1, Vec2f v2);

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