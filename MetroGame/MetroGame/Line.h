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
	std::list<GameLogic::Vec2f> filterData(const std::list<GameLogic::Vec2f> &data);
	bool compareVector(GameLogic::Vec2f &v1, GameLogic::Vec2f &v2);

	class Line
	{
	private:
		std::vector<float> distances;
		std::vector<GameLogic::Vec2f> positions;
		std::list<MetroStation> metroStations;
		std::list<std::pair<int, MetroStation>> stationIndex;
	public:
		Line() = delete;
		Line(const Line&) = delete;
		explicit Line(std::list<GameLogic::Vec2f> line, std::list<MetroStation> stations);
		~Line();

		std::size_t size() const;
		int getIndexByPosition(float position) const;
		const std::list<std::pair<int, MetroStation>>  getStationIndexes() const;
		float getStationDistance(MetroStation * station) const;
		const GameLogic::Vec2f& operator[](int i) const;
		float getDistance(int i) const;

		const std::vector<GameLogic::Vec2f> &getLine() const;
	};
}