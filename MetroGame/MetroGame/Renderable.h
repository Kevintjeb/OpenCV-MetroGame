#pragma once
<<<<<<< HEAD

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
=======
#include "Vec.h"
#include "Model.h"
class Renderable
{
public:
	Vec3f position;
	Vec3f rotation;
	Vec3f scale;
	Model model;
	float angle;
	Renderable(Vec3f position, Vec3f rotation, float angle, Vec3f scale, Model model);
	~Renderable();

private:
};
>>>>>>> 27830eb840d123bee5127e7ed837595c6b3aaecc
