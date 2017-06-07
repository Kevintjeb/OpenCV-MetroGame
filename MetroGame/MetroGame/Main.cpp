#include "system.h"
#include "Main.h"

using namespace mg_gameLogic;


//extern "C" {
//	_declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
//}

int main(int argc, char **argv)
{
	mg_system::init(argc, argv);
	mg_system::start();
}

