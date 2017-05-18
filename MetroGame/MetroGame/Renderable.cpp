#include "Renderable.h"



Renderable::Renderable(Vec3f position, Vec3f rotation, float angle, Vec3f scale, std::string model)
{
	this->position = position;
	this->rotation = rotation;
	this->angle = angle;
	this->scale = scale;
	this->model = model;
}


Renderable::~Renderable()
{
}