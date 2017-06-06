#include <list>
#include "Vect.h"
#include "Line.h"
#include <iostream>
#include "MetroTrain.h"

namespace mg_gameLogic
{
	class Test {
	public: 
		Test();
		Test(const Test&) = delete;
		~Test();
		Line line;
		MetroTrain train;
		std::list<GameLogic::Vec2f> testMetroLine();
	};
}
