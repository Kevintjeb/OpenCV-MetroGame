#include "Test.h"
#include "Line.h"

using namespace std;
using namespace mg_gameLogic;

mg_gameLogic::Test::Test() :line(testMetroLine())
{
	
}

mg_gameLogic::Test::~Test()
{
}

std::list<Vec2f> mg_gameLogic::Test::testMetroLine()
{
	std::list<Vec2f> dummy;
	
	dummy.push_front(Vec2f(0.0f, 0.0f));
	dummy.push_front(Vec2f(0.0f, 0.0f));
	for (int i = 0; i < 100; i++)
	{
		Vec2f vector = Vec2f((float)rand()/RAND_MAX, (float)rand()/RAND_MAX);
		dummy.push_back(vector);
		
	}
	dummy = filterData(dummy);
	return dummy;
	
}

