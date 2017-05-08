#include "system.h"

#include <GL/freeglut.h>

void mg_system::init(int &argc, char **argv)
{
	mg_system::_internal::freeglutInit(argc, argv);
	mg_system::_internal::RenderInit();
	mg_system::_internal::GameInit();
}

void mg_system::_internal::freeglutInit(int& argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitErrorFunc(mg_system::_internal::OnGlutError);
	glutInitWarningFunc(mg_system::_internal::OnGlutWarning);
	glutDisplayFunc(mg_system::_internal::OnDisplay);
	glutIdleFunc(mg_system::_internal::OnIdle);
	glutKeyboardFunc([](unsigned char key, int, int) {mg_system::_internal::OnKey(key); });
}

void mg_system::start()
{
	glutMainLoop();
}

void mg_system::redraw()
{
	glutPostRedisplay();
}