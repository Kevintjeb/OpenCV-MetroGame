#include "PauseScene.h"
#include "SceneManager.h"

Font* PauseScene::largeFont3D = nullptr;
Font* PauseScene::largeFont2D = nullptr;

PauseScene::PauseScene()
{
	SceneManager::getInstance().switchWindow3D();
	if (!largeFont3D)
		largeFont3D = new Font("font_72.fnt");
	SceneManager::getInstance().switchWindow2D();
	if (!largeFont2D)
		largeFont2D = new Font("font_72.fnt");

	this->width = SceneManager::getInstance().getWidth();
	this->height = SceneManager::getInstance().getHeight();
}


PauseScene::~PauseScene()
{
}

void PauseScene::render2D()
{
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, height, 0, -100, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glDisable(GL_DEPTH_TEST);

	glColor4f(0, 0, 0, 1);
	largeFont2D->drawText(pauseString, width / 2 - largeFont2D->textLength(pauseString) / 2, height / 2);

	glEnable(GL_DEPTH_TEST);
}

void PauseScene::render3D()
{
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, height, 0, -100, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glDisable(GL_DEPTH_TEST);

	glColor4f(0, 0, 0, 1);
	largeFont3D->drawText(pauseString, width / 2 - largeFont3D->textLength(pauseString) / 2, height / 2);
	glEnable(GL_DEPTH_TEST);
}

void PauseScene::update()
{
}

void PauseScene::onEnter()
{
}

void PauseScene::onExit()
{
}

void PauseScene::onKeyUP(unsigned char key)
{
	if (key == ' ') {
		SceneManager::getInstance().unPauseScene();
	}
}

void PauseScene::onKeyDown(unsigned char)
{
}

void PauseScene::onIdle()
{
}

void PauseScene::onSpecialFunc(int)
{
}

void PauseScene::onSpecialUpFunc(int)
{
}

void PauseScene::reshapeFunc(int, int)
{
}
