#include "RenderableOutput.h"

using namespace mg_gameLogic;
using namespace std;

list<Renderable> renderables(0);
list<RenderableLine> lines(0);

RenderablePointer mg_gameLogic::allocate_renderable(Renderable& renderable)
{
	renderables.push_back(renderable);
	return std::prev(renderables.end());
}

LinePointer mg_gameLogic::allocate_line(RenderableLine& line)
{
	lines.push_back(line);
	return std::prev(lines.end());
}

void mg_gameLogic::clear_renderables() {
	renderables.clear();
	lines.clear();
}

void mg_gameLogic::clear_lines()
{
	lines.clear();
}


void mg_gameLogic::deallocate_renderable(RenderablePointer renderable)
{
	renderables.erase(renderable);
	
}

void mg_gameLogic::deallocate_line(LinePointer line)
{
	lines.erase(line);
}

list<Renderable>& mg_gameLogic::get_renderables()
{
	return renderables;
}

list<RenderableLine>& mg_gameLogic::get_lines()
{
	return lines;
}