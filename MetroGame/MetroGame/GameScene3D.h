#pragma once
#include <GL\freeglut.h>
#include "system.h"
#include "iostream"
#include "ModelLoader.h"

#include "IScene.h"
#include "Font.h"
#include "Vect.h"
#include "Line.h"
#include <math.h>
#define _USE_MATH_DEFINES
#include <cstdio>
#include <map>
#include <time.h>

#include "VertexClass.h"
#include "Renderable.h"

#include "Texture.h"
#include "MetroTrain.h"

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
	void render2D() override;
	void render3D() override;
	void update() override;
	void onEnter() override;
	void onExit() override;
	void onKeyUP(unsigned char) override;
	void onKeyDown(unsigned char) override;
	void onIdle() override;
	void onSpecialFunc(int) override;
	void onSpecialUpFunc(int) override;
	void reshapeFunc(int, int) override;
};

