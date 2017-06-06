#pragma once

#include "Vect.h"
#include "Model.h"
#include <string>

namespace mg_gameLogic
{
	class Renderable
	{
	public:
		GameLogic::Vec3f position, rotation, scale;
		float angle;
		std::string model;

		Renderable();
		Renderable(const Renderable&);
		Renderable(std::string model, GameLogic::Vec3f pos, float angle, GameLogic::Vec3f rot, GameLogic::Vec3f scale = GameLogic::Vec3f(1, 1, 1));
		~Renderable();
	};
}