#pragma once
#include <string>
#include "GL/freeglut.h"

class IScene;

class SceneManager
{
public:
	void loadScene(IScene &);
	IScene& getCurrentScene();
	void render();
	int getWidth();
	int getHeight();
	void createWindow3D(int, int, std::string);
	void createWindow2D(int, int, std::string);
	void tick();
	void onKeyUp(unsigned char);
	void onKeyDown(unsigned char);
	void onIdle();
	void onSpecialFunc(int key);
	void onSpecialUpFunc(int key);
	void reshapeFunc(int, int);
	void init();
	static SceneManager& getInstance();

private:
	int width, height;
	GLuint windowID;
	bool isInit = false;
	SceneManager(const SceneManager&);
	SceneManager();
	~SceneManager();
	IScene* currentScene;
};



