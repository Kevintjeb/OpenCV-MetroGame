#include "Timetable.h"

mg_gameLogic::Timetable::Timetable(std::list<Line> lines, std::vector<MetroStation> stations): lines(lines), stations(stations)
{
	for (MetroStation &s : stations) 
	{
		setWalkableNodes(s);
	}
	for (MetroStation station : stations)
	{
		preCalcedDistances.insert<station, 999999>;
	}
}



void mg_gameLogic::Timetable::setWalkableNodes(MetroStation stationToSet) 
{
	std::list<MetroStation> connectedNodes(0);
	for (MetroStation &station : stations)
	{
		for (Line *l : stationToSet.connectedLines)
		{
			auto result = std::find(std::begin(station.connectedLines), std::end(station.connectedLines), l);
			if (result != station.connectedLines.end())
			{
				connectedNodes.push_back(station);
			}
		}
	}
	stationToSet.connectedStations = connectedNodes;

}

float mg_gameLogic::Timetable::getWeight(MetroStation current, MetroStation target) 
{
	Line * matchingLine;
	for (Line * line : current.connectedLines) 
	{
		auto result = std::find(std::begin(target.connectedLines), std::end(target.connectedLines), line);
		if (result != target.connectedLines.end())
		{
			matchingLine = line;
			break;
		}
	}
	return abs(matchingLine->getStationDistance(current) - matchingLine->getStationDistance(target));
}

mg_gameLogic::MetroStation mg_gameLogic::Timetable::findPath(MetroStation start, MetroStation goal)
{
	std::map<MetroStation, float> distances;
	distances.insert(preCalcedDistances.begin(), preCalcedDistances.end());
	std::vector<MetroStation> unexploredStations = stations;
	for (MetroStation station : unexploredStations) 
	{
		station.parent = nullptr;
	}
	distances[start] = 0;
	while (unexploredStations.size() > 0) 
	{
		MetroStation current = getMin(distances);
		if (current == goal) 
		{
			return goal;
		}

		unexploredStations.erase(std::remove(unexploredStations.begin(), unexploredStations.end(), current), unexploredStations.end());
		for (MetroStation st : current.connectedStations) 
		{
			float dist = distances[current] + getWeight(current, st);
			if (dist < distances[st]) 
			{
				distances[st] = dist;
				st.parent = &current;
			}
		}
	}
	return start;
}



mg_gameLogic::MetroStation mg_gameLogic::Timetable::getMin(std::map<mg_gameLogic::MetroStation, float> mymap)
{
	std::pair<mg_gameLogic::MetroStation, float>min
		= *min_element(mymap.begin(), mymap.end(), CompareSecond());
	return min.first;
}