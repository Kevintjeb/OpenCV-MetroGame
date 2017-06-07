#include "Test.h"
#include "Line.h"
#include "MetroStation.h"

using namespace std;
using namespace mg_gameLogic;

mg_gameLogic::Test::Test() :line(testMetroLine(), {}), train(&line)
{
	
}

mg_gameLogic::Test::~Test()
{
}

std::list<Vec2f> mg_gameLogic::Test::testMetroLine()		//Creates Dummy Data for metro line
{
	std::list<Vec2f> dummy;
	
	dummy.push_front(Vec2f(0.0f, 0.0f));
	dummy.push_front(Vec2f(0.0f, 0.0f));
	//for (int i = 0; i < 50; i++)
	//{
	//	Vec2f vector = Vec2f((float)rand()/RAND_MAX, (float)rand()/RAND_MAX);
	//	dummy.push_back(vector);
	//	
	//}
	dummy.push_back(Vec2f(0.25, 0.25));
	dummy.push_back(Vec2f(0.50, 0.30));
	dummy.push_back(Vec2f(0.75, 0.50));
	dummy.push_back(Vec2f(0.85, 0.75));
	dummy.push_back(Vec2f(0.25, 0.90));
	dummy.push_back(Vec2f(0.15, 0.60));
	dummy.push_back(Vec2f(0.35, 0.65));
	dummy.push_back(Vec2f(0.55, 0.75));


	//dummy = filterData(dummy);
	return dummy;
	
}

