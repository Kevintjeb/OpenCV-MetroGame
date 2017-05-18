#include "Renderable.h"

using namespace mg_gameLogic;

Renderable::Renderable() : model(METRO), position(Vec3f()), rotation(Vec3f()), scale(Vec3f())
{

}

Renderable::Renderable(const Renderable& render) : model(render.model), angle(render.angle), position(render.position), rotation(render.rotation), scale(render.scale)
{

}


Renderable::Renderable(Model model, Vec3f pos ,float angle, Vec3f rot, Vec3f scale) : model(model), position(pos), rotation(rot), scale(scale), angle(angle)
{
}

Renderable::~Renderable()
{
}