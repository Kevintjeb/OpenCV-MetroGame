#include "MainMenuScene.h"
#include <iostream>
#include "SceneManager.h"
#include "GameScene3D.h"
#include "PauseScene.h"

Font* MainMenuScene::largeFont2D = nullptr;
Font* MainMenuScene::smallFont2D = nullptr;
Font* MainMenuScene::largeFont3D = nullptr;
Font* MainMenuScene::smallFont3D = nullptr;
IScene* MainMenuScene::gameInstance = nullptr;


void MainMenuScene::drawStrings()
{

}

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

	if (!gameInstance)
		gameInstance = new GameScene3D();

	this->width = SceneManager::getInstance().getWidth();
	this->height = SceneManager::getInstance().getHeight();

	//appendText(Text(width/2 - largeFont3D->textLength("Main Menu")/2, height / 3, largeFont3D, "Main Menu"));
	appendText(Text(width/2 - smallFont3D->textLength("Press any button to play!")/2, height - 200, smallFont3D, "Press any button to play!"));
}

MainMenuScene::~MainMenuScene()
{
}

void MainMenuScene::appendText(Text &string)
{
	text.push_back(string);
}

void MainMenuScene::renderLogo()
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
	logoTexture.Bind();
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

void MainMenuScene::render3D() {


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
	glColor4f(1,1,1,1);

/*
	largeFont3D->drawText(mainString, width / 2 - largeFont3D->textLength(mainString) / 2, height / 3);
	smallFont3D->drawText(startString, width / 2 - smallFont3D->textLength(startString) / 2, height / 2);
*/
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
	lastTime = glutGet(GLUT_ELAPSED_TIME);

}

void MainMenuScene::update()
{
	if (this->text.at(0).getX() >= 200 && this->text.at(0).getX() <= 1400 && !reversing)
	{
		this->text.at(0).setX(text.at(0).getX() + 100 * deltaTime);
	}
	else
	{
		reversing = true;
		this->text.at(0).setX(text.at(0).getX() - 100 * deltaTime);
		if(this->text.at(0).getX() <= 800)
			reversing = false;
	}
}

void MainMenuScene::onIdle()
{
	int currentTime = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = (currentTime - lastTime) / 1000.0f;
	lastTime = currentTime;
}

void MainMenuScene::onKeyUP(unsigned char key)
{
}

void MainMenuScene::onKeyDown(unsigned char key)
{
	if (key == 27)
		exit(0);
	else
		SceneManager::getInstance().loadScene(gameInstance);
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
	for (Text& t : text) {
		t.setX(width/2 - t.getFont()->textLength(t.getText()) /2);
	}
}
