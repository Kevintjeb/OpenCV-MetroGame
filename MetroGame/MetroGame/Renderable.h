#pragma once

#include "Vect.h"
#include "Model.h"
#include <string>

namespace mg_gameLogic
{
	class Renderable
	{
	public:
		Vec3f position, rotation, scale;
		float angle;
		Model model;

		Renderable();
		Renderable(const Renderable&);
		Renderable(Model model, Vec3f pos, float angle, Vec3f rot = Vec3f(0, 0, 0) , Vec3f scale = Vec3f(1, 1, 1));
		~Renderable();
	};
}