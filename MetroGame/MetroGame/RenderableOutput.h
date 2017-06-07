#pragma once

#include "Renderable.h"
#include <list>

namespace mg_gameLogic
{
	using RenderablePointer = std::list<Renderable>::iterator;
	using LinePointer = std::list<RenderableLine>::iterator;

	RenderablePointer allocate_renderable(Renderable&);
	LinePointer allocate_line(RenderableLine&);

	void deallocate_renderable(RenderablePointer);
	void deallocate_line(LinePointer);
	void clear_renderables();

	std::list<Renderable>& get_renderables();
	std::list<RenderableLine>& get_lines();


}