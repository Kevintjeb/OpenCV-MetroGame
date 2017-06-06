#include "system.h"
#include "Test.h"
#include "Main.h"

using namespace mg_gameLogic;

int main(int argc, char **argv)
{
	//Test test;
	//test.testMetroLine();
	mg_system::init(argc, argv);
	mg_system::start();

}

