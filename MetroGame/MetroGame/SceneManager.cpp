#include "SceneManager.h"
#include "MainMenuScene.h"
#include "GameScene.h"


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
		this->currentScene = new GameScene();
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
	}
	else throw "Scenemanager not initialized";
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