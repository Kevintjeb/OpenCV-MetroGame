#include "MetroStation.h"
#include "RenderableOutput.h"

using namespace mg_gameLogic;
using namespace std;

MetroStation::MetroStation()
{
	addPassengers(rand() % 100 + 50);
	PPS = rand() % 5 + 1;				//Passenggers Per Second
}



mg_gameLogic::MetroStation::MetroStation(Vec2f pos, int id) :
	position(pos), stationID(id),
	pointer(allocate_renderable(Renderable("models/city/city.obj", {pos.x, -78, pos.y}, 0, {0, 1, 0}, {0.1f, 0.1f, 0.1f} )))
{

}

MetroStation::~MetroStation()
{
	deallocate_renderable(pointer);
}
//Changes the postition of the MetroStation -> DEPRECATED (this has been replaced in gamelogic branch)
void mg_gameLogic::MetroStation::setPosition(Vec2f pos)
{
	position = pos;
	pointer->position = Vec3f(pos.x*50,-92,pos.y*50);
}

bool mg_gameLogic::MetroStation::operator==(const MetroStation & other) const
{
	if (this->stationID == stationID) 
	{
		return true;
	}
	return false;
}

void mg_gameLogic::MetroStation::addPassengers(int amountToAdd)
{
	for (int i = 0; i < amountToAdd; i++)
	{
		int stationToAddTo = stationID;
		while (stationToAddTo == stationID) {
			stationToAddTo = rand() % passengers.size();
		}
		passengers[stationToAddTo]++;
	}
}

void mg_gameLogic::MetroStation::addPassengers(int amountToAdd, int id)
{
	passengers[id] += amountToAdd;
}

bool mg_gameLogic::MetroStation::operator!=(const MetroStation & other) const
{
	if (this->stationID != stationID)
	{
		return true;
	}
	return false;
}

bool mg_gameLogic::MetroStation::operator<(const MetroStation & other) const
{
	if (this->stationID < stationID) 
	{
		return true;
	}
	return false;
}

void mg_gameLogic::MetroStation::update(float deltaTime)
{
	elapseTime += deltaTime/1000;
	if (deltaTime > 1) 
	{
		elapseTime--;
		addPassengers(PPS);
	}
}

int mg_gameLogic::MetroStation::getAmountOfPassengers(std::vector<int> passengers)
{
	int amountOfPassengers = 0;
	for (int i = 0; i < passengers.size(); i++)
	{
		amountOfPassengers += passengers[i];
	}
	return amountOfPassengers;
}

std::vector<int> mg_gameLogic::MetroStation::getPassengers(int nextStationID, int freeSeats)
{
	std::vector<int> passengersToShip;
	std::vector<int> correctTarget;
	for (int i = 0; i < paths.size(); i++) 
	{
		if (paths[i] == nextStationID) 
		{
			correctTarget.push_back(i);
		}
	}
	int i = 0;
	while (i < freeSeats)
	{
		int target = rand() % correctTarget.size();
		passengers[correctTarget[i]]--;
		passengersToShip[correctTarget[i]]++;
		i++;
	}

	return passengersToShip;
}


