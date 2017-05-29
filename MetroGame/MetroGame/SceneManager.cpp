#include "SceneManager.h"
#include "MainMenuScene.h"
#include "GameScene.h"
#include "GameScene3D.h"
#include "system.h"

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
		createWindow3D(800, 600, "3D window");
		this->width = 800;
		this->height = 600;
		this->currentScene = new GameScene3D();
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
void SceneManager::loadScene(IScene &newScene)
{
	if (isInit) {
		currentScene->onExit();
		delete currentScene; //remove it
		currentScene = &newScene;
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

void SceneManager::render()
{
	if (isInit) {
		currentScene->render();
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

void SceneManager::createWindow3D(int width, int height, std::string name)
{
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	windowID = glutCreateWindow(name.c_str());
	glEnable(GL_DEPTH_TEST);

	glutInitErrorFunc(mg_system::_internal::OnGlutError);
	glutInitWarningFunc(mg_system::_internal::OnGlutWarning);
	glutDisplayFunc([]() {SceneManager::getInstance().render(); });
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

}

void SceneManager::createWindow2D(int width, int height, std::string name)
{
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	windowID = glutCreateWindow(name.c_str());
	glEnable(GL_DEPTH_TEST);

	glutInitErrorFunc(mg_system::_internal::OnGlutError);
	glutInitWarningFunc(mg_system::_internal::OnGlutWarning);
	glutDisplayFunc([]() {SceneManager::getInstance().render(); });
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

}

void SceneManager::tick()
{
	if (isInit) {
		currentScene->update();
	}
	else throw "Scenemanager not initialized";
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
		glutPostRedisplay();
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