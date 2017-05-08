#include "system.h"

#include <GL\freeglut.h>

using namespace mg_system;

void mg_system::_internal::RenderInit()
{
	GLuint window_id = initWindow("hans", 600, 600, OnDisplay);
	GLuint window_it = initWindow("jollie", 600, 600, OnDisplay);

	glClearColor(0, 0, 0, 1);
}

void mg_system::_internal::OnDisplay()
{
	glutSwapBuffers();
}