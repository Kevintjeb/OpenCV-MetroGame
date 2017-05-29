#include "system.h"

#include <GL/freeglut.h>
#include "ModelLoader.h"
#include "SceneManager.h"

void mg_system::init(int &argc, char **argv)
{
	mg_system::_internal::freeglutInit(argc, argv);
	mg_system::_internal::GameInit();
	SceneManager::getInstance().init();
}

void mg_system::_internal::freeglutInit(int& argc, char **argv)
{
	glutInit(&argc, argv);	
}
//
//GLuint mg_system::initWindow(std::string name, int width, int height, void (*renderer)())
//{
//	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
//	glutInitWindowSize(800, 800);
//	GLuint window_id = glutCreateWindow(name.c_str());
//	glEnable(GL_DEPTH_TEST);
//
//	glutInitErrorFunc(mg_system::_internal::OnGlutError);
//	glutInitWarningFunc(mg_system::_internal::OnGlutWarning);
//	glutDisplayFunc([]() {SceneManager::getInstance().render();});
//	glutIdleFunc([]() {SceneManager::getInstance().onIdle(); });
//	glutKeyboardFunc([](unsigned char key, int, int) {SceneManager::getInstance().onKeyDown(key); });
//	glutKeyboardUpFunc([](unsigned char key, int, int) {SceneManager::getInstance().onKeyUp(key); });
//	glutReshapeFunc([](int w, int h) {SceneManager::getInstance().reshapeFunc(w, h); });
//
//	glutSpecialFunc([](int key, int, int)
//	{
//		SceneManager::getInstance().onSpecialFunc(key);
//	});
//
//	glutSpecialUpFunc([](int key, int, int)
//	{
//		SceneManager::getInstance().onSpecialUpFunc(key);
//	});
//
//	return window_id;
//}

void mg_system::start()
{
	glutMainLoop();
}
