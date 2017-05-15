#include "system.h"

#include <GL\freeglut.h>

using namespace mg_system;
extern bool keys[255];
void mg_system::_internal::GameInit()
{
	
}

void mg_system::_internal::OnIdle()
{
	redraw();
}

void mg_system::_internal::OnKey(unsigned char key)
{
	if (key == 27) {
		exit(0);
	}
	keys[key] = true;
}

void mg_system::_internal::OnKeyUp(unsigned char key)
{
	keys[key] = false;
}