#pragma once
#include <list>
#include "Renderable.h"
#include "RenderableOutput.h"
#include <vector>
#include <functional>
#include <array>
namespace mg_gameLogic 
{
	class Line;
	class MetroStation
	{
	public:	
		static constexpr int stationCount = 10;

		MetroStation();
		MetroStation(Vec2f pos, int id = -1); //TODO Vervangen door echte waarde
		~MetroStation();
		Vec2f position;
		void setPosition(Vec2f pos);
		int stationID;
		std::list<Line*> connectedLines;
		std::list<MetroStation> connectedStations;
		MetroStation * parent;
		bool operator==(const MetroStation &other) const;
	
		std::vector<int> paths;
		std::array<int, stationCount> passengers;
		int maxPassengers = 200;
		void addPassengers(int amountToAdd);
		void addPassengers(int amountToAdd, int id);
		int PPS;
		bool qrCodePlaced;
		bool operator !=(const MetroStation &other) const;
		bool operator <(const MetroStation &other) const;
		void update(float deltaTime, std::vector<Vec2f> qrcodes);
		int getAmountOfPassengers(std::vector<int> passengers);
		std::vector<int>getPassengers(int nextStationID,int freeSeats);
	private:
		RenderablePointer pointer;
		float elapseTime = 0;

	};


}
