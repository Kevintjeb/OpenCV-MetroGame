#include "MainMenuScene.h"
#include <iostream>
#include "SceneManager.h"
#include "GameScene3D.h"

Font* MainMenuScene::largeFont2D = nullptr;
Font* MainMenuScene::smallFont2D = nullptr;
Font* MainMenuScene::largeFont3D = nullptr;
Font* MainMenuScene::smallFont3D = nullptr;


MainMenuScene::MainMenuScene()
{
	SceneManager::getInstance().switchWindow2D();
	if (!largeFont2D)
		largeFont2D = new Font("font_72.fnt");
	if (!smallFont2D)
		smallFont2D = new Font("font_0.fnt");
	SceneManager::getInstance().switchWindow3D();
	if (!largeFont3D)
		largeFont3D = new Font("font_72.fnt");
	if (!smallFont3D)
		smallFont3D = new Font("font_0.fnt");
}

MainMenuScene::~MainMenuScene()
{
}

void MainMenuScene::render3D() {

	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, height, 0, -100, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glDisable(GL_DEPTH_TEST);
	
	glColor4f(0, 0, 0, 1);
	largeFont3D->drawText(mainString, width / 2 - largeFont3D->textLength(mainString) / 2, height / 3);
	smallFont3D->drawText(startString, width / 2 - smallFont3D->textLength(startString) / 2, height / 2);
	//smallFont->drawText("Exit", width / 2 - smallFont->textLength("Exit") / 2, height / 2 + 50);

	glEnable(GL_DEPTH_TEST);
}

void MainMenuScene::render2D()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, height, 0, -100, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glDisable(GL_DEPTH_TEST);

	glColor4f(0, 0, 0, 1);
	largeFont2D->drawText("2D view", width / 2 - largeFont2D->textLength("2D view") / 2, height / 2);
	glEnable(GL_DEPTH_TEST);
}

void MainMenuScene::onEnter() {
	//Do some onEnter stuff, maybe intro animation?
	this->width = SceneManager::getInstance().getWidth();
	this->height = SceneManager::getInstance().getHeight();
	std::cout << "Entered MainMenuScene" << std::endl;
}

void MainMenuScene::update()
{
	std::cout << "Update MainMenuScene" << std::endl;
}

void MainMenuScene::onIdle()
{
	glutPostRedisplay();
}

void MainMenuScene::onKeyUP(unsigned char key)
{
}

void MainMenuScene::onKeyDown(unsigned char key)
{
	if (key == 27)
		exit(0);
	else
		SceneManager::getInstance().loadScene(new GameScene3D());
}

void MainMenuScene::onSpecialFunc(int)
{
}

void MainMenuScene::onSpecialUpFunc(int)
{
}

void MainMenuScene::onExit() {
	//Do some onEnter stuff, maybe outro animation or sound.?
	std::cout << "Exit MainMenuScene" << std::endl;
}

void MainMenuScene::reshapeFunc(int w, int h) {
	width = w;
	height = h;
}
