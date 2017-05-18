#pragma once
#include "Vec.h"
#include "Model.h"
#include <string>
class Renderable
{
public:
	Vec3f position;
	Vec3f rotation;
	Vec3f scale;
	std::string model;
	float angle;
	Renderable(Vec3f position, Vec3f rotation, float angle, Vec3f scale, std::string model);
	~Renderable();

private:
};
