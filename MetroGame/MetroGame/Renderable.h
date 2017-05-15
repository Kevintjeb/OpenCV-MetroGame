#pragma once
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
