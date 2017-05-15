#include "Renderable.h"

<<<<<<< HEAD
using namespace mg_gameLogic;

Redenderable::Redenderable() : position(Vec3f()), rotation(Vec3f()), scale(Vec3f())
{

}

Redenderable::Redenderable(const Redenderable& render) : position(render.position), rotation(render.position), scale(render.scale)
{

}


Redenderable::Redenderable(Vec3f pos ,float angle, Vec3f rot, Vec3f scale) : position(pos), rotation(rot), scale(scale), angle(angle)
{
}

Redenderable::~Redenderable()
{

=======


Renderable::Renderable(Vec3f position, Vec3f rotation, float angle, Vec3f scale, Model model)
{
	this->position = position;
	this->rotation = rotation;
	this->angle = angle;
	this->scale = scale;
	this->model = model;
}


Renderable::~Renderable()
{
>>>>>>> 27830eb840d123bee5127e7ed837595c6b3aaecc
}