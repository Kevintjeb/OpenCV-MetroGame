#include "system.h"

#include <GL\freeglut.h>

//using namespace system;

void mg_system::_internal::RenderInit()
{
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(800, 800);
	glutCreateWindow("window name");

	glClearColor(0, 0, 0, 1);
}

void mg_system::_internal::OnDisplay()
{
	glutSwapBuffers();
}