#pragma once
#include <list>
#include "Line.h"
#include <algorithm>
#include <iostream>
#include <list>
#include <vector>
namespace mg_gameLogic
{
	class Timetable
	{
	public:
		Timetable(std::list<Line> lines, std::vector<MetroStation> stations);
		void setWalkableNodes(MetroStation stationToSet);
		
		/////DEPRECATED
		//void createTimeTable(MetroStation station);
		//std::list<int> findSecondary(int stationID, MetroStation startStation);
		//std::list<int> pathFinder(int stationID, MetroStation startStation, std::list<int> path, int i);

	private:
		std::list<Line> lines;
		std::vector<MetroStation> stations;
	};
}