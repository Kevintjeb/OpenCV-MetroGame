#pragma once
#include "Renderable.h"

namespace mg_gameLogic
{
	class MetroLine
	{
	public:
		Redenderable *renderable;
	    Vec2f line;

		MetroLine(Vec2f openCV);
		~MetroLine();
	};
}
