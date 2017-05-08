#include "system.h"

int main(int argc, char **argv)
{
	mg_system::init(argc, argv);
	mg_system::start();
}