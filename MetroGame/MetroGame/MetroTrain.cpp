#include "MetroTrain.h"
#include <cmath>

using namespace mg_gameLogic;
using namespace std;

inline Vec2f MetroTrain::pos2d_from_pos(float pos)
{
	int index = line.getIndexByPosition(pos);

	Vec2f far = line[index+1], close = line[index];

	Vec2f normal(close.x - far.x, close.y - far.y);
	float mag = sqrt(normal.x*normal.x + normal.y*normal.y);
	normal.x /= mag;
	normal.y /= mag;

	float dist = line.getDistance(index) - pos;
	normal.x *= dist;
	normal.y *= dist;

	Vec2f pos2d(close.x + normal.x, close.y + normal.y);
	return pos2d;
}

inline float MetroTrain::checkAndSetPosRange(float pos)
{
	switch (state)
	{
	case State::FORWARD:
		if (pos >= line.getDistance(line.size() - 1))
		{
			state = State::BACKWARD;
			return line.getDistance(line.size() - 1) - (size*train_length);
		}
		break;
	case State::BACKWARD:
		if (pos <= 0)
		{
			state = State::FORWARD;
			return size*train_length;
		}
		break;
	}

	return pos;
}

inline std::tuple<Vec2f, float> mg_gameLogic::MetroTrain::findComplementaryPositionAndDistance(float pos)
{
	
}

MetroTrain::MetroTrain(const Line& line, float init_pos, State state, int size) :
	line(line), line_pos(init_pos), state(state), size(size), trains(0)
{
	
}

void MetroTrain::Recalculate(float elapsedTime)
{
	// ensuring we have the correct size
	if (trains.size() < size) // if we have to little trains
	{
		int diff = size - trains.size(); // we need 'diff' new trains
		for (int i = 0; i < diff; ++i) // we allocate new Renderables 
			trains.push_back(allocate_renderable(Renderable(METRO, Vec3f(0, -92.0f, 0), 0.0f, Vec3f(0, 1, 0), Vec3f(2, 2, 2))));
	}
	else if (trains.size() > size) // if we have to many trains
	{
		for (int i = trains.size() - 1; i >= size; --i) // from back to front
		{
			deallocate_renderable(trains[i]); // remove it from the list
			trains.pop_back(); // remove it from the vector
		}
	}

	line_pos += elapsedTime*speed * (state == State::FORWARD ? 1 : -1);

	line_pos = checkAndSetPosRange(line_pos);

	auto npos = pos2d_from_pos(line_pos);
	trains[0]->position.x = npos.x*50;
	trains[0]->position.z = npos.y*50;
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