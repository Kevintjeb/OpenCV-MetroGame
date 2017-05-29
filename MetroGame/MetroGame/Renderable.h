#pragma once

#include "Vect.h"
#include "Model.h"
#include <string>

namespace mg_

{
	class Renderable
	{
	public:
		Vec3f position, rotation, scale;
		float angle;
		std::string model;

		Renderable();
		Renderable(const Renderable&);
		Renderable(std::string model, Vec3f pos, float angle, Vec3f rot, Vec3f scale = Vec3f(1, 1, 1));
		~Renderable();
	};
}