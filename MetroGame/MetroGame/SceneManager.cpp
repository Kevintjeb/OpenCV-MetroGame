#include "SceneManager.h"
#include "MainMenuScene.h"
#include "system.h"
#include <functional>
#include "PauseScene.h"

IScene* SceneManager::pauseSceneVar = nullptr;

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

void mg_system::init(int &argc, char ** argv)
{
	glutInit( &argc, argv);
	SceneManager::getInstance().init();
}

void mg_system::start()
{
	glutMainLoop();
}

/*
 Initialize SceneManager;
*/
void SceneManager::init() {
	if (!isInit) {
		window3D = createWindow(1920, 1080, "3D window", []() {SceneManager::getInstance().render3D(); });
		HGLRC context3D = wglGetCurrentContext();
		glutFullScreen();

		window2D = createWindow(1920, 1080, "2D window", []() {SceneManager::getInstance().render2D(); });
		HGLRC context2D = wglGetCurrentContext();
		glutFullScreen();

		if (!wglShareLists(context3D, context2D))
		{
			printf("Error sharing lists\n");
		}	

		this->width = 1920;
		this->height = 1080;

#ifdef _DEBUG
		this->currentScene = new MainMenuScene();
#elif
		this->currentScene = new MainMenuScene();
#endif


		if (!pauseSceneVar)
			pauseSceneVar = new PauseScene();
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

void SceneManager::pauseScene()
{
	if (isInit && !isPaused) {
		isPaused = true;
		pausedScene = currentScene;
		currentScene = pauseSceneVar;
		currentScene->onEnter();
	}
	else return;
}

void SceneManager::unPauseScene() {
	if (isInit && isPaused) {
		isPaused = false;
		currentScene = pausedScene;
		currentScene->onEnter();
		pausedScene = nullptr;
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

	glutSetIconTitle(name.c_str());

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

GLuint SceneManager::getWindow3D()
{
	return window3D;
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
		tick();
		currentScene->onIdle();

		glutSetWindow(window3D);
		glutPostRedisplay();

		glutSetWindow(window2D);
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