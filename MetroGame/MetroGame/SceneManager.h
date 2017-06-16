#pragma once
#include <string>
#include "GL/freeglut.h"
#include <vector>
#include "GameScene3D.h"

class IScene;

class SceneManager
{
public:
	void loadScene(IScene *);
	void pauseScene();
	void unPauseScene();
	IScene& getCurrentScene();
	int getWidth();
	int getHeight();
	void init();
	static SceneManager& getInstance();
	void switchWindow2D();
	void switchWindow3D();
	GLuint getWindow3D();

private:
	int width, height;
	GLuint window2D, window3D;
	bool isInit = false;
	SceneManager(const SceneManager&);
	SceneManager();
	~SceneManager();
	void onKeyUp(unsigned char);
	void onKeyDown(unsigned char);
	void onIdle();
	void onSpecialFunc(int key);
	void onSpecialUpFunc(int key);
	void reshapeFunc(int, int);
	GLuint createWindow(int, int, std::string, void(*callback)());
	void render3D();
	void render2D();
	void tick();
	IScene* currentScene;
	bool isPaused;
	IScene* pausedScene;

	static IScene* pauseSceneVar;

};



