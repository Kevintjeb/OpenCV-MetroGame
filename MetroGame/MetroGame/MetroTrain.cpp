#include "MetroTrain.h"

using namespace mg_gameLogic;
using namespace std;

inline Vec2f mg_gameLogic::MetroTrain::pos2d_from_pos(float pos)
{
	int index = line.getIndexByPosition(pos);

	Vec2f far = line[index+1], close = line[index];

	float slope = (far.y - close.y) / (far.x - close.x);

	float x = close.x;
	float b = close.y - (x*slope);
	float val = (pos - line.getDistance(index)) / (line.getDistance(index+1) - line.getDistance(index));
	x += val;
	float y = x*slope + b;	 

	Vec2f pos2d(x, y);

	return pos2d;
}

MetroTrain::MetroTrain(const Line& line, float init_pos, int size) :
	line(line), line_pos(init_pos), size(size), trains(0)
{

}

void MetroTrain::Recalculate(float elapsedTime)
{
	// ensuring we have the correct size
	if (trains.size() < size) // if we have to little trains
	{
		int diff = size - trains.size(); // we need 'diff' new trains
		for (int i = 0; i < diff; ++i) // we allocate new Renderables 
			trains.push_back(allocate_renderable(Redenderable(Vec3f(0, 0, 0), 0.0f)));
	}
	else if (trains.size() > size) // if we have to many trains
	{
		for (int i = trains.size() - 1; i >= size; --i) // from back to front
		{
			deallocate_renderable(trains[i]); // remove it from the list
			trains.pop_back(); // remove it from the vector
		}
	}

	line_pos += elapsedTime*speed;

	auto npos = pos2d_from_pos(line_pos);
	trains[0]->position.x = npos.x;
	trains[0]->position.y = npos.y;
}

int MetroTrain::get_size() const
{
	return size;
}

void MetroTrain::resize(int nsize)
{
	if (nsize > 0 && nsize <= max_size)
		size = nsize;
}