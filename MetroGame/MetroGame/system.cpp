#include "system.h"

#include <GL/freeglut.h>
#include "ModelLoader.h"
#include "SceneManager.h"


void mg_system::init(int &argc, char **argv)
{
	mg_system::_internal::freeglutInit(argc, argv);
	SceneManager::getInstance().init();
}

void mg_system::_internal::freeglutInit(int& argc, char **argv)
{
	glutInit(&argc, argv);	
}

void mg_system::start()
{
	glutMainLoop();
}
