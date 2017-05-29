#include "MainMenuScene.h"
#include <iostream>
#include "SceneManager.h"
#include "GameScene.h"

Font* MainMenuScene::largeFont = nullptr;
Font* MainMenuScene::smallFont = nullptr;

MainMenuScene::MainMenuScene(int w, int h)
{
	this->width = w;
	this->height = h;

	if(!largeFont)
		largeFont = new Font("font_72.fnt");
	if(!smallFont)
		smallFont = new Font("font_0.fnt");

}


MainMenuScene::~MainMenuScene()
{
}

void MainMenuScene::render() {

	glClearColor(0.6f, 0.6f, 1, 1);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, height, 0, -100, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor4f(1, 1, 1, 1);
	glDisable(GL_DEPTH_TEST);
	
	largeFont->drawText("Main Menu", width / 2 - largeFont->textLength("Main Menu") / 2, height / 3);
	smallFont->drawText("Play", width / 2 - smallFont->textLength("Play") / 2, height / 2);
	smallFont->drawText("Exit", width / 2 - smallFont->textLength("Exit") / 2, height / 2 + 50);
	glutSwapBuffers();
}

void MainMenuScene::onEnter() {
	//Do some onEnter stuff, maybe intro animation?
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
	std::cout << "onKeyUp GameScene" << std::endl;
	if (key == 'q') {
		SceneManager::getInstance().loadScene(*new GameScene());
	}
	if (key == 27) {
		exit(0);
	}
}

void MainMenuScene::onKeyDown(unsigned char)
{
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
	glViewport(0, 0, w, h);
}
