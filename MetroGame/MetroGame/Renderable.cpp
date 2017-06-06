#include "Renderable.h"

using namespace mg_gameLogic;
using namespace std;

Renderable::Renderable() : model("models/Metro/metro.obj"), position(Vec3f()), rotation(Vec3f()), scale(Vec3f())
{

}

Renderable::Renderable(const Renderable& render) : model(render.model), angle(render.angle), position(render.position), rotation(render.rotation), scale(render.scale)
{

}


Renderable::Renderable(std::string model, Vec3f pos ,float angle, Vec3f rot, Vec3f scale) : model(model), position(pos), rotation(rot), scale(scale), angle(angle)
{
}

Renderable::Renderable(Vec3f pos, float angle, Vec3f rot, Vec3f scale) : position(pos), rotation(rot), scale(scale), angle(angle)
{
}

Renderable::~Renderable()
{
}

mg_gameLogic::RenderableLine::RenderableLine()
{
}

mg_gameLogic::RenderableLine::RenderableLine(const RenderableLine &)
{
}

mg_gameLogic::RenderableLine::RenderableLine(const std::vector<Vec2f>& l)
{
	line = vector<Vec3f>();
	for (Vec2f vi : l)
		line.push_back(Vec3f(vi.x, vi.y, 0));
}
