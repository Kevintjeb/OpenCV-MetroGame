#include "RenderableOutput.h"

using namespace mg_gameLogic;
using namespace std;

list<Redenderable> renderables(0);

RedenderablePointer mg_gameLogic::allocate_renderable(Redenderable& renderable)
{
	renderables.push_back(renderable);
	return std::prev(renderables.end());
}

void mg_gameLogic::deallocate_renderable(RedenderablePointer renderable)
{
	renderables.erase(renderable);
}

list<Redenderable>& mg_gameLogic::get_renderables()
{
	return renderables;
}