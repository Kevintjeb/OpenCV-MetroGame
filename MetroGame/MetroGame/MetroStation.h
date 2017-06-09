#pragma once
#include <list>
#include "Renderable.h"
#include "RenderableOutput.h"
namespace mg_gameLogic 
{

	class MetroStation
	{
	public:
		
		MetroStation();
		MetroStation(GameLogic::Vec2f pos, int id = -1); //TODO Vervangen door echte waarde
		~MetroStation();
		GameLogic::Vec2f position;
		void setPosition(GameLogic::Vec2f pos);
		int stationID;
	private:
		RenderablePointer pointer;
	};


}