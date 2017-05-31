#pragma once

#include "Renderable.h"
#include "Line.h"
#include "RenderableOutput.h"


#include <vector>
#include <tuple>

namespace mg_gameLogic
{
	class MetroTrain
	{
	public:
		enum class State
		{
			FORWARD,
			BACKWARD
		};

	private:
		const Line& line;
		float line_pos;
		State state;

		std::vector<RedenderablePointer> trains;
		int size;

		inline Vec2f pos2d_from_pos(float pos);
		inline float checkAndSetPosRange(float pos);

		// return: position and the position's distance
		// error : [∞, ∞], ∞
		inline std::pair<Vec2f, float> findComplementaryPositionAndDistance(float pos);

	public:
		static constexpr float speed        = 0.25f;
		static constexpr int   max_size     = 16;
		static constexpr float train_length = 0.25f;
		
		explicit MetroTrain(const Line& line, float init_pos = 0.0f, State state = State::FORWARD, int size = 1);

		void Recalculate(float elapsedTime);
		int get_size() const;
		void resize(int nsize);
	};
}