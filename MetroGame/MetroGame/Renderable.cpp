#include "Renderable.h"

using namespace mg_gameLogic;
using namespace std;

Renderable::Renderable() : model("models/Metro/metro.obj"), position(GameLogic::Vec3f()), rotation(GameLogic::Vec3f()), scale(GameLogic::Vec3f())
{

}

Renderable::Renderable(const Renderable& render) : model(render.model), angle(render.angle), position(render.position), rotation(render.rotation), scale(render.scale)
{

}


Renderable::Renderable(std::string model, GameLogic::Vec3f pos ,float angle, GameLogic::Vec3f rot, GameLogic::Vec3f scale) : model(model), position(pos), rotation(rot), scale(scale), angle(angle)
{
}

Renderable::Renderable(GameLogic::Vec3f pos, float angle, GameLogic::Vec3f rot, GameLogic::Vec3f scale) : position(pos), rotation(rot), scale(scale), angle(angle)
{
}

Renderable::~Renderable()
{
}

mg_gameLogic::RenderableLine::RenderableLine() : line(), type(LineType::NO_TYPE)
{
}

mg_gameLogic::RenderableLine::RenderableLine(const RenderableLine & r) : line(r.line), type(r.type)
{
}

mg_gameLogic::RenderableLine::RenderableLine(const std::vector<GameLogic::Vec2f>& l, LineType type) : type(type)
{
	line = vector<GameLogic::Vec3f>();
	for (GameLogic::Vec2f vi : l)
		line.push_back(GameLogic::Vec3f(vi.x, vi.y, 0));
}
