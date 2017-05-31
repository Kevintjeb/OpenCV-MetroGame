#pragma once
#include <string>
#include "GL/freeglut.h"
#include <vector>

class IScene;

class SceneManager
{
public:
	void loadScene(IScene *);
	IScene& getCurrentScene();
	int getWidth();
	int getHeight();
	void init();
	static SceneManager& getInstance();

private:
	int width, height;
	//GLuint windowID;
	std::vector<GLuint> windowIDS;
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
	void createWindow(int, int, std::string, void(*callback)());
	void render3D();
	void render2D();
	void tick();
	IScene* currentScene;
};



