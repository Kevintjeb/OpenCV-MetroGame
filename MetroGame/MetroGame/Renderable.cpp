#include "Renderable.h"

using namespace mg_gameLogic;

Renderable::Renderable() : model("models/Metro/metro.obj"), position(GameLogic::Vec3f()), rotation(GameLogic::Vec3f()), scale(GameLogic::Vec3f())
{

}

Renderable::Renderable(const Renderable& render) : model(render.model), angle(render.angle), position(render.position), rotation(render.rotation), scale(render.scale)
{

}


Renderable::Renderable(std::string model, GameLogic::Vec3f pos ,float angle, GameLogic::Vec3f rot, GameLogic::Vec3f scale) : model(model), position(pos), rotation(rot), scale(scale), angle(angle)
{
}

Renderable::~Renderable()
{
}