#include <list>
#include "Vect.h"
#include "Line.h"
#include <iostream>

namespace mg_gameLogic
{
	class Test {
	public: 
		Test();
		~Test();
		Line line;
		std::list<Vec2f> testMetroLine();
	};
}
