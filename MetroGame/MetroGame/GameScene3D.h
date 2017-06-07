#pragma once
#include "IScene.h"
class GameScene3D :
	public IScene
{
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

