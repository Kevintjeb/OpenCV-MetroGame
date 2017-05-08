#include "Test.h"

mg_gameLogic::Test::Test()
{
}

mg_gameLogic::Test::~Test()
{
}

void mg_gameLogic::Test::testMetroLine()
{
	std::list<Vec2f> dummy;
	
	dummy.push_front(Vec2f(5, 5));
	dummy.push_front(Vec2f(5, 5));
	for (int i = 0; i < 100; i++)
	{
		Vec2f vector = Vec2f(rand(), rand());
		dummy.push_back(vector);
	}
	MetroLine metro = MetroLine(dummy);
}
