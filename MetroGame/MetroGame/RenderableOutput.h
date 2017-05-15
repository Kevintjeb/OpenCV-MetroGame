#pragma once

#include "Renderable.h"
#include <list>

namespace mg_gameLogic
{
	using RedenderablePointer = std::list<Renderable>::iterator;

	RedenderablePointer allocate_renderable(Renderable&);
	void deallocate_renderable(RedenderablePointer);

	std::list<Renderable>& get_renderables();
}