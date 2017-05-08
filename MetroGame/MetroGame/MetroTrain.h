#pragma once

#include "Renderable.h"
#include <vector>

namespace mg_gameLogic
{
	class MetroTrain
	{
	public:
		float line_pos;
		std::vector<


		void Recalculate(float elapsedTime);

		int getsize();
		void resize(int nsize);
	private:
		std::vector<Redenderable*> redenderables;
		int size;
	};
}