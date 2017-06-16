#pragma once
#include <list>
#include "Line.h"
#include <algorithm>
#include <iostream>
#include <list>
#include <map>
#include <vector>
namespace mg_gameLogic
{
	class Timetable
	{
	public:
		Timetable(std::list<Line*> lines, std::vector<MetroStation> stations);
		void getPaths(MetroStation& goals);
		void setWalkableNodes(MetroStation &stationToSet);

		float getWeight(MetroStation& current,MetroStation& target);
		MetroStation findPath(MetroStation& start,MetroStation& goal);

		mg_gameLogic::MetroStation getMin(std::map<mg_gameLogic::MetroStation, float> mymap, std::vector<MetroStation>);
		
		/////DEPRECATED
		//void createTimeTable(MetroStation station);
		//std::list<int> findSecondary(int stationID,MetroStation& startStation);
		//std::list<int> pathFinder(int stationID,MetroStation& startStation, std::list<int> path, int i);
		typedef std::pair<mg_gameLogic::MetroStation, float> MyPairType;
		struct CompareSecond
		{
			bool operator()(const MyPairType& left, const MyPairType& right) const
			{
				return left.second < right.second;
			}
		};
	private:
		std::list<Line*> lines;
		std::vector<MetroStation> tstations;
		std::map<MetroStation, float> preCalcedDistances;

	};
}