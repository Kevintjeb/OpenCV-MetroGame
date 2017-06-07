#include "SceneManager.h"
#include "MainMenuScene.h"
#include "system.h"
#include <functional>

SceneManager::SceneManager(const SceneManager &other)
{
	this->currentScene = other.currentScene;
}
/*
	Constructor to initialize a SceneManager.
*/
SceneManager::SceneManager()
{
}

/*
 Initialize SceneManager;
*/
void SceneManager::init() {
	if (!isInit) {
		window3D = createWindow(800, 600, "3D window", []() {SceneManager::getInstance().render3D(); });
		HGLRC context3D = wglGetCurrentContext();
		window2D = createWindow(800, 600, "2D window", []() {SceneManager::getInstance().render2D(); });
		HGLRC context2D = wglGetCurrentContext();

		if (!wglShareLists(context3D, context2D))
		{
			printf("Error sharing lists\n");
		}
		this->width = 800;
		this->height = 600;
		this->currentScene = new MainMenuScene();
		isInit = true;
	}
	else {
		return;
	}
}


SceneManager::~SceneManager()
{
}

/*
Method to load a new Scene.
The currentScene its onExit will be called, then it will be deleted.
Afterwards the newScene its onEnter will be called.
*/
void SceneManager::loadScene(IScene *newScene)
{
	if (isInit) {
		currentScene->onExit();
		delete currentScene; //remove it
		currentScene = newScene;
		currentScene->onEnter();
	}
	else return;
}

/*
Function to return the current active scene.
*/
IScene& SceneManager::getCurrentScene() {
	if (isInit) {
		return *currentScene;
	}
	else throw "Scenemanager not initialized";
}

void SceneManager::render3D()
{
	if (isInit) {
		currentScene->render3D();
		glutSwapBuffers();
	}
	else throw "Scenemanager not initialized";
}

void SceneManager::render2D()
{
	if (isInit) {
		currentScene->render2D();
		glutSwapBuffers();
	}
	else throw "Scenemanager not initialized";
}

int SceneManager::getWidth()
{
	return width;
}

int SceneManager::getHeight()
{
	return height;
}

GLuint SceneManager::createWindow(int width, int height, std::string name, void(* callback)())
{
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	GLuint windowID = glutCreateWindow(name.c_str());
	glEnable(GL_DEPTH_TEST);
	glutDisplayFunc(callback);
	glutInitErrorFunc(mg_system::_internal::OnGlutError);
	glutInitWarningFunc(mg_system::_internal::OnGlutWarning);
	
	glutIdleFunc([]() {SceneManager::getInstance().onIdle(); });
	glutKeyboardFunc([](unsigned char key, int, int) {SceneManager::getInstance().onKeyDown(key); });
	glutKeyboardUpFunc([](unsigned char key, int, int) {SceneManager::getInstance().onKeyUp(key); });
	glutReshapeFunc([](int w, int h) {SceneManager::getInstance().reshapeFunc(w, h); });

	glutSpecialFunc([](int key, int, int)
	{
		SceneManager::getInstance().onSpecialFunc(key);
	});

	glutSpecialUpFunc([](int key, int, int)
	{
		SceneManager::getInstance().onSpecialUpFunc(key);
	});

	return windowID;
}

void SceneManager::tick()
{
	if (isInit) {
		currentScene->update();
	}
	else throw "Scenemanager not initialized";
}

void SceneManager::switchWindow2D()
{
	glutSetWindow(window2D);
}

void SceneManager::switchWindow3D()
{
	glutSetWindow(window3D);
}

void SceneManager::onKeyUp(unsigned char key)
{
	if (isInit) {
		currentScene->onKeyUP(key);
	}
	else throw "Scenemanager not initialized";
}

void SceneManager::onKeyDown(unsigned char key)
{
	if (isInit) {
		currentScene->onKeyDown(key);
	}
	else throw "Scenemanager not initialized";
}

void SceneManager::onIdle()
{
	if (isInit) {
		currentScene->onIdle();

		glutSetWindow(window3D);
		glutPostRedisplay();

		glutSetWindow(window2D);
		glutPostRedisplay();
		tick();
	}
	else throw "Scenemanager not initialized";
}

void SceneManager::onSpecialFunc(int key)
{
	if (isInit) {
		currentScene->onSpecialFunc(key);
	}
	else throw "Scenemanager not initialized";
}

void SceneManager::onSpecialUpFunc(int key)
{
	if (isInit) {
		currentScene->onSpecialUpFunc(key);
	}
	else throw "Scenemanager not initialized";
}

void SceneManager::reshapeFunc(int w, int h)
{
	if (isInit) {
		currentScene->reshapeFunc(w, h);
		this->width = w;
		this->height = h;
		glViewport(0, 0, w, h);
	}
	else throw "Scenemanager not initialized";
}

/*
Singleton function to return the instance.
For flobo van elzelingen.
*/
SceneManager & SceneManager::getInstance()
{
	static SceneManager instance = SceneManager();
	return instance;
}