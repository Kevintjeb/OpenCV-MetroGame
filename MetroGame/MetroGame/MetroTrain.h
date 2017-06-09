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
		Line *line;
		float line_pos;
		State state;
		float totalTimeSpend = 0;
		float speeddif = 0;
		int stopState = 0;	//0= normaal rijden // 1 = gestopt // 2 = optrekken 
		int oldIndex = -1;  //zorgt voor de eerste check zodat niet meerdere keren stopt.

		std::vector<RenderablePointer> trains;
		int size;

		inline GameLogic::Vec2f pos2d_from_pos1d(float pos);
		inline float checkAndSetPosRange(float pos);

		// return: position and the position's distance
		// error : [NaN, Nan], Nan
		inline std::pair<GameLogic::Vec2f, float> findComplementaryPositionAndDistance(float pos);

	public:
		static constexpr float scale = 0.60f;
		float speed = 1.f*scale;
		static constexpr int   max_size     = 16;
		static constexpr float train_length = 0.2f*scale;
		static constexpr float train_spacing = 0.025f*scale;
		static constexpr bool __debug_output = false;
		
		explicit MetroTrain(Line* line, float init_pos = 0.0f, State state = State::FORWARD, int size = 1);
		float getSpeed(float);
		void Recalculate(float elapsedTime);
		int get_size() const;
		void resize(int nsize);
		void reposistion(Line* line);
	};
}