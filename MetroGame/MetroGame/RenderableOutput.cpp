#include "RenderableOutput.h"

using namespace mg_gameLogic;
using namespace std;

list<Renderable> renderables(0);

RedenderablePointer mg_gameLogic::allocate_renderable(Renderable& renderable)
{
	renderables.push_back(renderable);
	return std::prev(renderables.end());
}

void mg_gameLogic::deallocate_renderable(RedenderablePointer renderable)
{
	renderables.erase(renderable);
}

list<Renderable>& mg_gameLogic::get_renderables()
{
	return renderables;
}