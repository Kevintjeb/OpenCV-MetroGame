#pragma once

#include "Vect.h"
#include <list>
#include <memory>
#define MARGINX 0.8
#define MARGINY 0.8
#include <valarray>

namespace mg_gameLogic
{
	std::list<Vec2f> filterData(const std::list<Vec2f> &data);
	bool compareVector(Vec2f &v1,Vec2f &v2);

	enum class LineType
	{
		Red, Blue, Green
	};

	class Line
	{
	private:
		std::valarray<float> distances;
		std::valarray<Vec2f> positions;
	public:
		const LineType type;

		Line() = delete;
		Line(const Line&) = delete;
		explicit Line(std::list<Vec2f> line, LineType type);
		~Line();
		
		std::size_t size() const;
		int getIndexByPosition(float position) const;
		const Vec2f& operator[](int i) const;
		float getDistance(int i) const;
	};
}