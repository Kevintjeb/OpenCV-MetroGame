#include "MetroTrain.h"

using namespace mg_gameLogic;
using namespace std;

MetroTrain::MetroTrain(const Line& line, float init_pos, int size) : 
	line(line), line_pos(init_pos), size(size), trains(max_size)
{

}

void MetroTrain::Recalculate(float elapsedTime)
{
	// ensuring we have the correct size
	if (trains.size() < size) // if we have to little trains
	{
		int diff = size - trains.size(); // we need 'diff' new trains
		for (int i = 0; i < diff; ++i) // we allocate new Renderables 
			trains.push_back(allocate_renderable(Redenderable(Vec3f(0, 0, 0))));
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

	int index = line.getIndexByPosition(line_pos);
	Vec2f pos = line[index];
	trains[0]->position.x = pos.x;
	trains[0]->position.y = pos.y;
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