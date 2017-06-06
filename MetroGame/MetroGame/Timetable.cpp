#include "Timetable.h"

mg_gameLogic::Timetable::Timetable(std::list<Line> lines, std::vector<MetroStation> stations): lines(lines), stations(stations)
{
	//Calculate Directly Connected Stations
	for (MetroStation &s : stations) 
	{
		setWalkableNodes(s);
	}
}

void mg_gameLogic::Timetable::setWalkableNodes(MetroStation stationToSet) 
{
	std::list<int> connectedNodes(0);
	for (MetroStation &station : stations)
	{
		for (Line *l : stationToSet.connectedLines)
		{
			auto result = std::find(std::begin(station.connectedLines), std::end(station.connectedLines), l);
			if (result != station.connectedLines.end())
			{
				connectedNodes.push_back(station.stationID);
			}
		}
	}
	stationToSet.connectedStations = connectedNodes;
}




////DEPRECATED
//void mg_gameLogic::Timetable::createTimeTable(MetroStation stationToSet)
//{
//	std::vector<int> timetab(0);
//	timetab.assign(stations.size() - 1 ,-2);
//	timetab[stationToSet.stationID] = -1;
//	for (MetroStation &station : stations) 
//	{
//		for (Line *l : stationToSet.connectedLines) 
//		{
//			auto result = std::find(std::begin(station.connectedLines), std::end(station.connectedLines), l);
//			if (result != station.connectedLines.end()) 
//			{
//				timetab[station.stationID] == station.stationID;
//			}
//		}
//	}
//	stationToSet.timetab = timetab;
//}
//
//std::list<int> mg_gameLogic::Timetable::findSecondary(int stationID, MetroStation startStation)
//{
//	std::list<int> shortestPath;
//	for (int i = 0; i < startStation.timetab.size();i++) 
//	{
//		std::list<int> newPath = pathFinder(stationID, startStation, shortestPath, i);
//		if (newPath.size()< shortestPath.size()) 
//		{
//			shortestPath = newPath;
//		}
//	}
//}
//
//std::list<int> mg_gameLogic::Timetable::pathFinder(int stationIDtoFind, MetroStation currentStation, std::list<int> path, int i) 
//{
//	if (currentStation.timetab[i] >= 0)
//	{
//		path.push_back(i);
//		//Directe verbinding 
//		if (stations[i].stationID == stationIDtoFind)
//		{
//			return path;
//		}
//		else
//		{
//			for(int j = 0 ; j<currentStation.)
//			pathFinder(stationIDtoFind, stations[i], path, i);
//		}
//		path.pop_back();
//	}
//}
