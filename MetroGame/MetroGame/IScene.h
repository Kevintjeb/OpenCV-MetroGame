#pragma once

class IScene
{
public:
	IScene();
	~IScene();

	virtual void render2D() = 0; //method to render graphics
	virtual void render3D() = 0; //method to render graphics
	virtual void update() = 0; //method to be called every update for other things beside graphics
	virtual void onEnter() = 0; //method to be called when entering scene
	virtual void onExit() = 0; //method to be called when switching from this scene
	virtual void onKeyUP(unsigned char) = 0;
	virtual void onKeyDown(unsigned char) = 0;
	virtual void onIdle() = 0;
	virtual void onSpecialFunc(int) = 0;
	virtual void onSpecialUpFunc(int) = 0;
	virtual void reshapeFunc(int, int) = 0;

protected:
	int width, height;
};

