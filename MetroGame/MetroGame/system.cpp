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
}

GLuint mg_system::initWindow(std::string name, int width, int height, void (*renderer)())
{
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(800, 800);
	GLuint window_id = glutCreateWindow(name.c_str());

	glutInitErrorFunc(mg_system::_internal::OnGlutError);
	glutInitWarningFunc(mg_system::_internal::OnGlutWarning);
	glutDisplayFunc(renderer);
	glutIdleFunc(mg_system::_internal::OnIdle);
	glutKeyboardFunc([](unsigned char key, int, int) {mg_system::_internal::OnKey(key); });

	return window_id;
}

void mg_system::start()
{
	glutMainLoop();
}

void mg_system::redraw()
{
	glutPostRedisplay();
}