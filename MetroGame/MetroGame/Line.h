#pragma once

#include "Vect.h"
#include <list>
#include <memory>
#define MARGINX 0.8
#define MARGINY 0.8
#include <valarray>
#include "MetroStation.h"
#include <vector>

namespace mg_gameLogic
{
	std::list<Vec2f> filterData(const std::list<Vec2f> &data);
	bool compareVector(Vec2f &v1,Vec2f &v2);

	class Line
	{
	private:
		std::vector<float> distances;
		std::vector<Vec2f> positions;
		std::list<MetroStation> metroStations;
		std::vector<std::pair<int, MetroStation>> stationIndex;
	public:
		Line() = delete;
		Line(const Line&) = delete;
		explicit Line(std::list<Vec2f> line, std::list<MetroStation> stations);
		~Line();
		
		std::size_t size() const;
		int getIndexByPosition(float position) const;
		const std::vector<std::pair<int, MetroStation>>  getStationIndexes() const;
		float getStationDistance(MetroStation * station) const;
		const Vec2f& operator[](int i) const;
		float getDistance(int i) const;

		const std::vector<Vec2f> &getLine() const;
	};
}