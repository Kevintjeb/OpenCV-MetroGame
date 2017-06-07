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
		bool operator <(const MetroStation &other) const;
		std::vector<int> paths;
	private:
		RenderablePointer pointer;
	};


}