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
		MetroStation(Vec2f pos, int id = -1); //TODO Vervangen door echte waarde
		~MetroStation();
		Vec2f position;
		void setPosition(Vec2f pos);
		int stationID;
	private:
		RenderablePointer pointer;
	};


}