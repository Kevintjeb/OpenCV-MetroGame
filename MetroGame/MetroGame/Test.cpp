#include "Test.h"
#include "Line.h"

using namespace std;
using namespace mg_gameLogic;

mg_gameLogic::Test::Test()
{

}

mg_gameLogic::Test::~Test()
{
}

void mg_gameLogic::Test::testMetroLine()
{
	std::list<Vec2f> dummy;
	
	dummy.push_front(Vec2f(0.0f, 0.0f));
	dummy.push_front(Vec2f(0.0f, 0.0f));
	for (int i = 0; i < 100; i++)
	{
		Vec2f vector = Vec2f(rand()/RAND_MAX, rand()/RAND_MAX);
		dummy.push_back(vector);
		
	}
	Line metro(dummy);
}
