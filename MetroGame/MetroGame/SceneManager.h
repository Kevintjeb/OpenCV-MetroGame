#pragma once

class IScene;

class SceneManager
{
public:
	void loadScene(IScene &);
	IScene& getCurrentScene();
	void render();
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
	bool isInit = false;
	SceneManager(const SceneManager&);
	SceneManager();
	~SceneManager();
	IScene* currentScene;
};



