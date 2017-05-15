#pragma once

#include "Vect.h"
#include <string>

namespace mg_gameLogic
{
	class Redenderable
	{
	public:
		Vec3f position, rotation, scale;
		float angle;
		void * data; // this will point to the model

		Redenderable();
		Redenderable(const Redenderable&);
		Redenderable(/*@Kevin @Rick add your vars*/ Vec3f pos, float angle, Vec3f rot = Vec3f(0, 0, 0) , Vec3f scale = Vec3f(1, 1, 1));
		~Redenderable();
	};
}