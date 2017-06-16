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

	textY = height - 200;
	textX = width / 2 - largeFont2D->textLength(pauseString) / 2;
}

PauseScene::~PauseScene()
{
}


void PauseScene::renderLogo()
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
	largeFont2D->drawText(pauseString, width / 2 - largeFont2D->textLength(pauseString) / 2, height - 200);

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

	renderLogo();

	glColor4f(0, 0, 0, 1);
	largeFont2D->drawText(pauseString, textX, textY);
	glEnable(GL_DEPTH_TEST);
}

bool reversingp = false;
void PauseScene::update()
{
	std::cout << "Update MainMenuScene" << std::endl;
	if (textX >= 200 && textX <= 1400 && !reversingp)
	{
		textX += 1;
	}
	else
	{
		reversingp = true;
		textX -= 1;

		if (textX <= 800)
			reversingp = false;
	}
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
