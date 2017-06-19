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
		MetroStation(GameLogic::Vec2f pos, int id = -1); //TODO Vervangen door echte waarde
		~MetroStation();
		GameLogic::Vec2f position;
		void setPosition(GameLogic::Vec2f pos);
		int stationID;
		std::list<Line*> connectedLines;
		std::list<MetroStation> connectedStations;
		MetroStation * parent;
		bool operator==(const MetroStation &other) const;
	
		std::array<int, stationCount> paths{0};
		std::array<int, stationCount> passengers{0};
		int maxPassengers = 200;
		void addPassengers(int amountToAdd);
		void addPassengers(int amountToAdd, int id);
		int PPS;
		bool qrCodePlaced;
		bool operator !=(const MetroStation &other) const;
		bool operator <(const MetroStation &other) const;
		void update(float deltaTime, std::vector<Vec2f> qrcodes);
		int getAmountOfPassengers(std::vector<int> passengers);
		std::array<int, MetroStation::stationCount> getPassengers(int nextStationID,int freeSeats);
	private:
		RenderablePointer pointer;
		float elapseTime = 0;

	};


}
