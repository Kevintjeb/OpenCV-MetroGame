#include "MetroStation.h"
#include "RenderableOutput.h"

using namespace mg_gameLogic;
using namespace std;

MetroStation::MetroStation()
{
}

mg_gameLogic::MetroStation::MetroStation(Vec2f pos, int id) : position(pos), stationID(id)
{
	
}

MetroStation::~MetroStation()
{
	//TODO find someway to fix this
	//deallocate_renderable(pointer);
}
//Changes the postition of the MetroStation -> DEPRECATED (this has been replaced in gamelogic branch)
void mg_gameLogic::MetroStation::setPosition(Vec2f pos)
{
	position = pos;
	RenderablePointer p = *pointer;
	p->position = Vec3f(pos.x*50,-92,pos.y*50);
}
