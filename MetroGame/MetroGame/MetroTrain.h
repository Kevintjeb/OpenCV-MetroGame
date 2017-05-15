#pragma once

#include "Renderable.h"
#include "Line.h"
#include "RenderableOutput.h"

#include <vector>

namespace mg_gameLogic
{
	class MetroTrain
	{
	private:
		const Line& line;
		float line_pos;

		std::vector<RedenderablePointer> trains;
		int size;

		inline Vec2f pos2d_from_pos(float pos);
	public:
		static constexpr float speed = 1.0f;
		static constexpr int max_size = 16;
		
		explicit MetroTrain(const Line& line, float init_pos = 0.0f, int size = 1);

		void Recalculate(float elapsedTime);
		int get_size() const;
		void resize(int nsize);
	};
}