#include "GameScene.h"
#include <iostream>
#include "gl/freeglut.h"
#include "MainMenuScene.h"
#include "SceneManager.h"
GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::render()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0f, 800 / (float)600, 0.1f, 200000);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	gluLookAt(100, 100, 100,
		0, 0, 0,
		0, 1, 0);

	glBegin(GL_QUADS);
	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
	glVertex3f(0, 0, 0);
	glVertex3f(-50, 0, 50);
	glVertex3f(0, 0, 100);
	glVertex3f(50, 0, 50);

	glColor4f(0.0f, 1.0f, 0.0f, 1.0f);

	glVertex3f(0, 3, 0);
	glVertex3f(-50, 3, 50);
	glVertex3f(0, 3, 100);
	glVertex3f(50, 3, 50);

	glColor4f(0.6f, 0.2f, 0.2f, 1.0f);

	glVertex3f(0, 3, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(-50, 0, 50);
	glVertex3f(-50, 3, 50);


	glVertex3f(0, 3, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(50, 0, 50);
	glVertex3f(50, 3, 50);

	glVertex3f(0, 3, 100);
	glVertex3f(0, 0, 100);
	glVertex3f(-50, 0, 50);
	glVertex3f(-50, 3, 50);

	glVertex3f(0, 3, 100);
	glVertex3f(0, 0, 100);
	glVertex3f(50, 0, 50);
	glVertex3f(50, 3, 50);
	glEnd();

	std::cout << "Rendering" << std::endl;
}

void GameScene::update()
{
	std::cout << "Update GameScene" << std::endl;
}

void GameScene::onEnter()
{
	std::cout << "Entered GameScene" << std::endl;
}

void GameScene::onExit()
{
	std::cout << "Exited GameScene" << std::endl;
}

void GameScene::onKeyUP(unsigned char key)
{
	std::cout << "onKeyUp GameScene" << std::endl;
	if (key == 'q') {
		SceneManager::getInstance().loadScene(*new MainMenuScene());
	}
}

void GameScene::onKeyDown(unsigned char)
{
	std::cout << "onKeyDown GameScene" << std::endl;
}

void GameScene::onIdle()
{
	glutPostRedisplay();
}

void GameScene::onSpecialFunc(int)
{
	std::cout << "onSpecialFunc GameScene" << std::endl;
}

void GameScene::onSpecialUpFunc(int)
{
	std::cout << "onSpecialUpFunc GameScene" << std::endl;
}

void GameScene::reshapeFunc(int w, int h) {
	glViewport(0, 0, w, h);
}
