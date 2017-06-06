#include "Line.h"

using namespace mg_gameLogic;
using namespace std;

Line::Line(list<Vec2f> line, LineType type) : positions(line.size()), distances(line.size()), type(type)
{
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
			// we are the first point so our distance is 0
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

	int l, r;
	l = 0;
	r = size() - 1;
	while (true)
	{
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

const Vec2f& Line::operator[](int index) const
{
	return positions[index];
}

float mg_gameLogic::Line::getDistance(int i) const
{
	return distances[i];
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