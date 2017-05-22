#pragma once

#include "Renderable.h"
#include "Line.h"
#include <list>

namespace mg_gameLogic
{
	using RenderablePointer = std::list<Renderable>::iterator;
	using LinePointer = std::list<Line*>::iterator;

	RenderablePointer allocate_renderable(Renderable&);
	LinePointer allocate_line(Line*);

	void deallocate_renderable(RenderablePointer);
	void deallocate_line(LinePointer);

	std::list<Renderable>& get_renderables();
	std::list<Line*>& get_lines();


}