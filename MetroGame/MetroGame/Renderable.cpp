#include "Renderable.h"

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

}