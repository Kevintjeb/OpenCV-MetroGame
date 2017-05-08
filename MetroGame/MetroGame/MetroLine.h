#pragma once
#include "Renderable.h"
#include <list>
#define MARGINX	5
#define	MARGINY 5
namespace mg_gameLogic
{
	class MetroLine
	{
	public:
		Redenderable *renderable;
		
	    std::list<Vec2f> line;

		MetroLine(std::list<Vec2f> openCV);
		~MetroLine();
		
		std::list<Vec2f> filterData(std::list<Vec2f>  data);
		bool compareVector(Vec2f v1, Vec2f v2);
	};
}
