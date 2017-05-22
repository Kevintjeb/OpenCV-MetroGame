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
		MetroStation(Vec2f pos);
		~MetroStation();
	private:
		RedenderablePointer pointer;
	};


}