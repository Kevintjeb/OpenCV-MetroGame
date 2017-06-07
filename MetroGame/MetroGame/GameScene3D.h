#pragma once
#include <GL\freeglut.h>
#include "system.h"
#include "iostream"
#include "ModelLoader.h"

#include "IScene.h"
#include "Font.h"
#include "Vect.h"
#include "Test.h"
#include "Line.h"
#include <math.h>
#define _USE_MATH_DEFINES
#include <cstdio>
#include <map>
#include <time.h>

#include "VertexClass.h"
#include "Renderable.h"

#include "Model.h"
#include "Texture.h"

#include "stb_image.h"
#include "RenderableOutput.h"

#include "SceneManager.h"
#include "MainMenuScene.h"
#include "Passengers.h"

using namespace mg_system;
using namespace mg_gameLogic;
using std::cout;
using std::endl;



class GameScene3D :
	public IScene
{
private:
	static Font* largeFont3D;
	static Font* smallFont2D;

	string time;
	struct {
		float seconds = 0;
		int minutes = 0;
	}Time;
	void prepareTime(float deltaTime);

public:
	GameScene3D();
	~GameScene3D();

	// Inherited via IScene
	virtual void render2D() override;
	virtual void render3D() override;
	virtual void update() override;
	virtual void onEnter() override;
	virtual void onExit() override;
	virtual void onKeyUP(unsigned char) override;
	virtual void onKeyDown(unsigned char) override;
	virtual void onIdle() override;
	virtual void onSpecialFunc(int) override;
	virtual void onSpecialUpFunc(int) override;
	virtual void reshapeFunc(int, int) override;
};

