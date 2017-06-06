#pragma once

class IScene
{
protected:
	IScene();

public:
	virtual ~IScene();

	/*
		Function to draw 2D graphics in.
	*/
	virtual void render2D() = 0;
	/*
		Function to draw 3D graphics in.
	*/
	virtual void render3D() = 0; 
	/*
		Function gets called every tick, use this to update variables / logic.
	*/
	virtual void update() = 0;
	/*
		The first function after the constructor call. Warning : OpenGL may keep calling onIdle/Render3D|2D while onEnter isnt called yet.
	*/
	virtual void onEnter() = 0; 
	/*
		Function to be called when switching to another scene. Use this to delete used variables.
	*/
	virtual void onExit() = 0;
	/*
		Function that gets called with a key that has been released.
	*/
	virtual void onKeyUP(unsigned char) = 0;
	/*
		Function that gets called with a key that has been pressed.
	*/
	virtual void onKeyDown(unsigned char) = 0;
	/*
		OpenGL idle function, gets called by OpenGL
	*/
	virtual void onIdle() = 0;
	/*
		Function that gets called for special keys (e.g. shift key) when they are pressed.
	*/
	virtual void onSpecialFunc(int) = 0;
	/*
		Function that gets called for special keys (e.g. shift key) when they are released.
	*/
	virtual void onSpecialUpFunc(int) = 0;
	/*
		Function that gets called by OpenGLwhen the window resizes.
	*/
	virtual void reshapeFunc(int, int) = 0;

protected:
	/*
		Window width/height
	*/
	int width, height;
};

