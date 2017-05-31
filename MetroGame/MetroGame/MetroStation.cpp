#include "MetroStation.h"

using namespace mg_gameLogic;
using namespace std;

MetroStation::MetroStation()
{
}

mg_gameLogic::MetroStation::MetroStation(Vec2f pos, int id) : position(pos), stationID(id)
{
	Model m = CITY;
	pointer = allocate_renderable(Renderable(m, Vec3f(pos.x * 50, -92, pos.y * 50), 0, Vec3f(0, 0, 0),Vec3f(0.1125,0.1125,0.1125)));
}

MetroStation::~MetroStation()
{
	//TODO find someway to fix this
	//deallocate_renderable(pointer);
}

void mg_gameLogic::MetroStation::setPosition(Vec2f pos)
{
	position = pos;
	pointer->position = Vec3f(pos.x*50,-92,pos.y*50);
}
