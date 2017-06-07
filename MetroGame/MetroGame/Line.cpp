#include "Line.h"
#include "Renderable.h"
#include "MetroStation.h"

using namespace mg_gameLogic;
using namespace std;

mg_gameLogic::Line::Line(std::list<Vec2f> line, std::list<MetroStation> stations): positions(line.size()+stations.size()), distances(line.size() + stations.size()), metroStations(stations)
{
	for (MetroStation &station : stations) {
		pair<int, MetroStation> currentStation =  make_pair(-1, station);
		int i = 0;
		float previousDistance =999999;
		list<Vec2f>::iterator itr = line.begin();
		for (Vec2f &v: line)
		{
			i++;
			if (v.distance(currentStation.second.position) < previousDistance)
			{
				itr = line.begin();
				for (int j = 0; j <= i; j++) 
				{
					itr++;
				}
				previousDistance = v.distance(currentStation.second.position);
				currentStation.first = i;
			}
		}

		line.insert(itr, currentStation.second.position);
		stationIndex.push_back(currentStation);
	}

	int index = 0;
	// we itterate over all points in the line
	for (Vec2f &v : line)
	{
		positions[index] = v; // we copy the point to our array
		if (index) // unless we'are 0
		{
			// set our distance to the distance of the last point + the distance of the previus and current point
			distances[index] = distances[index - 1] + v.distance(positions[index - 1]);
		}
		else
			//then we  are the first point so our distance is 0
			distances[index] = 0;
		index++;
	}
}

Line::~Line()
{
	
}

size_t Line::size() const
{
	return distances.size();
}

int Line::getIndexByPosition(const float position) const
{
	// standard binary tree with interpolation
	// if the position is not in the list we get the point to the 'left' of it

	if (position < 0 ) return 0;
	if (position >= distances[size() - 1]) 
		return size() - 1;

	int l, r;
	l = 0;
	r = size() - 1;

#ifdef _DEBUG
	constexpr int max_iter = 10;
			  int     iter =  0;
#endif

	while (true)
	{
#ifdef _DEBUG
		if (iter++ >= max_iter) 
			throw "invalid position";
#endif

		int m = (l + r) / 2;
		if (distances[m] < position) // we are lower than our position
		{
			// if the point to our right is higher, position is inbetween our points, and we return the leftmost point
			if (m < size() - 1 && distances[m + 1] > position) return m;
			l = m + 1;
		}
		else if (distances[m] > position) // we are higher than our position
		{
			// if the point to our left is lower, position is inbetween our points, and we return the leftmost point
			if (m > 0 && distances[m - 1] < position) return m - 1;
			r = m - 1;
		}
		// position matches exactly we return
		else return m;
	}
}

const std::list<std::pair<int, MetroStation>> mg_gameLogic::Line::getStationPosistion() const
{
	return stationIndex;
}



const Vec2f& Line::operator[](int index) const
{
	return positions[index];
}

float mg_gameLogic::Line::getDistance(int i) const
{
	return distances[i];
}

const std::vector<Vec2f>& mg_gameLogic::Line::getLine() const
{
	return positions;
}

list<Vec2f> mg_gameLogic::filterData(const list<Vec2f> &data)
{
	std::list<Vec2f >  filtered;

	Vec2f previousVector = Vec2f(-1, -1);

	for (Vec2f vector : data)
	{
		if (compareVector(vector, previousVector)) {
			filtered.push_back(vector);
			previousVector = vector;
		}
	}
	return filtered;
}

bool mg_gameLogic::compareVector(Vec2f &v1,Vec2f &v2)
{

	if (abs(v1.x - v2.x) > MARGINX || abs(v1.y - v2.y) > MARGINY)
	{
		return true;
	}
	return false;
}