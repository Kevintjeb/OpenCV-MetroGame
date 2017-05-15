#pragma once

#include "Vect.h"
#include <list>
#include <memory>
#define MARGINX 5
#define MARGINY 5
#include <valarray>

namespace mg_gameLogic
{
	class Line
	{
	private:
		std::valarray<float> distances;
		std::valarray<Vec2f> positions;
	public:
		float *distances;
		Vec2f *positions;
		int length;
		
		Line() = delete;
		Line(std::list<Vec2f> line);
		std::list<Vec2f> filterData(std::list<Vec2f> data);
		bool compareVector(Vec2f v1, Vec2f v2);
		int getIndexByPosition(float position);
		Line() = delete;
		Line(const Line&) = delete;
		explicit Line(std::list<Vec2f> line);
		~Line();

		std::size_t size() const;
		int getIndexByPosition(float position) const;
		const Vec2f& operator[](int i) const;
	};
}