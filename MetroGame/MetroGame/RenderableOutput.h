#pragma once

#include "Renderable.h"
#include <list>

namespace mg_gameLogic
{
	using RedenderablePointer = std::list<Redenderable>::iterator;

	RedenderablePointer allocate_renderable(Redenderable&);
	void deallocate_renderable(RedenderablePointer);

	std::list<Redenderable>& get_renderables();
}