#pragma once
#include "Font.h"
#include "IScene.h"
#include "Texture.h"
class PauseScene : public IScene
{
	static Font *largeFont3D;
	static Font *largeFont2D;
	Texture logoTexture = Texture("logo.png");
	const string pauseString = "Game Paused!";

	int textY, textX = 0;

public:
	PauseScene();
	~PauseScene();
	void renderLogo();

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

