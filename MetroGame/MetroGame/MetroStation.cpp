#include "MetroStation.h"
#include "RenderableOutput.h"

using namespace mg_gameLogic;
using namespace std;

MetroStation::MetroStation()
{
	addPassengers(rand() % 100 + 50);
	PPS = rand() % 5 + 1; //Passenggers Per Second
}

mg_gameLogic::MetroStation::MetroStation(GameLogic::Vec2f pos, int id) :
	position(pos), stationID(id), passengers(),
	pointer(allocate_renderable(Renderable("models/station/station.obj", { pos.x * 50, -92, pos.y * 50 }, 0, { 0, 1, 0 }, { 0.1f, 0.1f, 0.1f })))
{
	paths = { 0 };
	passengers = { 0 };
	addPassengers(rand() % 100 + 50);
	PPS = rand() % 5 + 1;
}

MetroStation::~MetroStation()
{
//	deallocate_renderable(pointer);
}
//Changes the postition of the MetroStation -> DEPRECATED (this has been replaced in gamelogic branch)
void mg_gameLogic::MetroStation::setPosition(GameLogic::Vec2f pos)
{
	position = pos;
	pointer->position = GameLogic::Vec3f(pos.x*50,-92,pos.y*50);
}

bool mg_gameLogic::MetroStation::operator==(const MetroStation & other) const
{
	return this->stationID == other.stationID;
}


void mg_gameLogic::MetroStation::addPassengers(int amountToAdd)
{
	for (int i = 0; i < amountToAdd; i++)
	{
		int stationToAddTo = stationID;
		while (stationToAddTo == stationID) {
			stationToAddTo = rand() % stationCount;
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


	return this->stationID != other.stationID;
}

bool mg_gameLogic::MetroStation::operator<(const MetroStation & other) const
{
	return this->stationID < other.stationID;
}

void mg_gameLogic::MetroStation::update(float deltaTime, std::vector<GameLogic::Vec2f> qrcodes)
{
	qrCodePlaced = false;
	float marge = 0.001;
	for (GameLogic::Vec2f vec : qrcodes)
	{
		if (vec.x > position.x - marge && vec.x < position.x + marge && vec.y > position.y - marge && vec.y < position.y + marge)
		{
			qrCodePlaced = true;
		}
	}

	elapseTime += deltaTime / 1000;
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
//Returns the Vector of Passengers availeble for transfer
std::array<int, MetroStation::stationCount> mg_gameLogic::MetroStation::getPassengers(int nextStationID, int freeSeats)
{
	std::array<int, MetroStation::stationCount> passengersToShip;
	int i = 0;
	while (i < freeSeats)
	{
		int target = rand() % paths.size();
		if (paths[target] == nextStationID)
			passengers[target]--;
		passengersToShip[target]++;
		i++;
	}

	return passengersToShip;
}
