#pragma once
#include <list>
#include "Renderable.h"
#include "RenderableOutput.h"
#include <vector>

namespace mg_gameLogic 
{
	class Line;
	class MetroStation
	{
	public:		
		MetroStation();
		MetroStation(Vec2f pos, int id = -1); //TODO Vervangen door echte waarde
		~MetroStation();
		Vec2f position;
		void setPosition(Vec2f pos);
		int stationID;
		std::list<Line*> connectedLines;
		std::list<MetroStation> connectedStations;
		MetroStation * parent;
		bool operator ==(const MetroStation &other) const;
		std::vector<int> paths;
		std::vector<int> passengers;
		int maxPassengers = 200;
		void addPassengers(int amountToAdd);
		void addPassengers(int amountToAdd, int id);
		int PPS;
		
		bool operator !=(const MetroStation &other) const;
		bool operator <(const MetroStation &other) const;
		void update(float deltaTime);

	private:
		RenderablePointer pointer;
		float elapseTime = 0;

	};


}
