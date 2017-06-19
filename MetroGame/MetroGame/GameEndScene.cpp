#include <iostream>
#include "SceneManager.h"
#include "GameScene3D.h"
#include "PauseScene.h"
#include "GameEndScene.h"

Font* GameEndScene::largeFont2D = nullptr;
Font* GameEndScene::smallFont3D = nullptr;

void GameEndScene::drawStrings()
{

}

GameEndScene::GameEndScene()
{
	SceneManager::getInstance().switchWindow2D();
	if (!largeFont2D)
		largeFont2D = new Font("font_72.fnt");
	SceneManager::getInstance().switchWindow3D();
	logoTexture = new Texture("logo.png");
	if (!smallFont3D)
		smallFont3D = new Font("font_0.fnt");
}

GameEndScene::~GameEndScene()
{
}

void GameEndScene::appendText(Text &string)
{
	text.push_back(string);
}

void GameEndScene::renderLogo()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glAlphaFunc(GL_GREATER, 0.52f);
	glEnable(GL_BLEND);
	glEnable(GL_ALPHA_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//glDisable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, height, 0, -10, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor4f(1, 1, 1, 1);

	glEnable(GL_TEXTURE_2D);
	logoTexture->Bind();
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
	glTexCoord2f(0, 1);	glVertex3f(0, height, 0);
	glTexCoord2f(1, 1);	glVertex3f(width, height, 0);
	glTexCoord2f(1, 0);	glVertex3f(width, 0, 0);
	glEnd();
	//glEnable(GL_LIGHTING);

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
}

void GameEndScene::render3D() {


	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, height, 0, -100, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glDisable(GL_DEPTH_TEST);

	renderLogo();

	glColor4f(0, 0, 0, 1);

	for (Text& t : text) {
		t.getFont()->drawText(t.getText(), t.getX(), t.getY());
	}
	glColor4f(1, 1, 1, 1);

	/*
	largeFont3D->drawText(mainString, width / 2 - largeFont3D->textLength(mainString) / 2, height / 3);
	smallFont3D->drawText(startString, width / 2 - smallFont3D->textLength(startString) / 2, height / 2);
	*/
	glEnable(GL_DEPTH_TEST);
}

void GameEndScene::render2D()
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
	largeFont2D->drawText("Thanks for playing!", width / 2 - largeFont2D->textLength("Thanks for playing!") / 2, height / 2);
	glEnable(GL_DEPTH_TEST);
}

void GameEndScene::onEnter() {
	this->width = SceneManager::getInstance().getWidth();
	this->height = SceneManager::getInstance().getHeight();
	lastTime = glutGet(GLUT_ELAPSED_TIME);

	appendText(Text(width, height - 200, smallFont3D, "Thanks for playing!"));
}

void GameEndScene::update()
{
	if (this->text.at(0).getX() >= 200 && this->text.at(0).getX() <= 1400 && !reversing)
	{
		this->text.at(0).setX(text.at(0).getX() + 100 * deltaTime);
	}
	else
	{
		reversing = true;
		this->text.at(0).setX(text.at(0).getX() - 100 * deltaTime);
		if (this->text.at(0).getX() <= 800)
			reversing = false;
	}
}

void GameEndScene::onIdle()
{

	int currentTime = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = (currentTime - lastTime) / 1000.0f;
	lastTime = currentTime;
}

void GameEndScene::onKeyUP(unsigned char key)
{
}

void GameEndScene::onKeyDown(unsigned char key)
{
		exit(0);
}

void GameEndScene::onSpecialFunc(int)
{
}

void GameEndScene::onSpecialUpFunc(int)
{
}

void GameEndScene::onExit() {
	//Do some onEnter stuff, maybe outro animation or sound.?
	std::cout << "Exit MainMenuScene" << std::endl;
}

void GameEndScene::reshapeFunc(int w, int h) {
	width = w;
	height = h;
	for (Text& t : text) {
		t.setX(width / 2 - t.getFont()->textLength(t.getText()) / 2);
	}
}
