#include "MetroStation.h"
#include "RenderableOutput.h"

using namespace mg_gameLogic;
using namespace std;

MetroStation::MetroStation()
{
}

mg_gameLogic::MetroStation::MetroStation(GameLogic::Vec2f pos, int id) :
	position(pos), stationID(id),
	pointer(allocate_renderable(Renderable("models/city/city.obj", {pos.x, -78, pos.y}, 0, {0, 1, 0}, {0.1f, 0.1f, 0.1f} )))
{

}

MetroStation::~MetroStation()
{
	deallocate_renderable(pointer);
}
//Changes the postition of the MetroStation -> DEPRECATED (this has been replaced in gamelogic branch)
void mg_gameLogic::MetroStation::setPosition(GameLogic::Vec2f pos)
{
	position = pos;
	pointer->position = GameLogic::Vec3f(pos.x*50,-92,pos.y*50);
}
