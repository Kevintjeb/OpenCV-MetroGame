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
#include "Color.h"

using namespace mg_system;
using namespace mg_gameLogic;
using std::cout;
using std::endl;

class GameScene3D :
	public IScene
{
private:

	float randScale(float standScale);
	void createCityList();
	void initGroundPlane();
	void drawVertexArray(std::vector<VertexClass> verts, GLenum mode, int start, int end);
	void prepareModel(std::string modelPath);
	void move(float angle, float fac);
	void drawRenderables();
	void draw2DRenderables();
	Color getLineColor(LineType color);
	void prepare_lines();
	void prepare_lines2D();
	ModelLoader modelLoader;
	void setAllKeysFalse();

	struct {
		size_t points;
		bool is_game_over;
	}score = { 0, false };

	mg_gameLogic::MetroStation::Callback cb;

	std::map<std::string, int> modelsMap;
	std::map<std::string, int>::iterator it;
	std::list<MetroStation *> metroStations;
	GLuint window_db;

	LinePointer handle;
	Renderable testTrain;
	Line *line;
	MetroTrain *train;

	LinePointer handle2;
	Line *line2;
	MetroTrain *train2;

	LinePointer handle3;
	Line *line3;
	MetroTrain *train3;

	LinePointer handle4;
	Line *line4;
	MetroTrain *train4;

	LinePointer handle5;
	Line *line5;
	MetroTrain *train5;

	std::vector <VertexClass> TopPlane;
	std::vector <VertexClass> GroundPlane;
	std::vector <VertexClass> metroLines;
	std::vector <std::pair<int, int>> metroLinesPosition;
	std::vector <VertexClass> metroLines2D;
	std::vector <std::pair<int, int>> metroLinesPosition2D;
	std::vector<Texture*> textures;
	std::vector<RenderablePointer> renderablePointers;
	std::vector<Passengers> passengers;

	int oldTime = -1;

	int lastTime = 0;
	float rotation = 0.0f;

	int speed = 25;
	bool keys[255];
	bool shiftActive = false;
	string fps = "";
	float deltaTime = 0.0f;

	struct Camera
	{
		float posX = 7.57;
		float posY = -103.79;
		float rotX = 0;
		float rotY = 0;
		float height = 41.07;
	} camera;

	struct Camera2D
	{
		float posX = 0;
		float posY = 0;
		float rotX = 90;
		float rotY = 0;
		float height = -80;
	}camera2D;

	static Font* largeFont3D;

	string timeString;
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

