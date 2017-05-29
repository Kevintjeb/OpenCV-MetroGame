#pragma once
#include "IScene.h"
class GameScene3D :
	public IScene
{
public:
	GameScene3D();
	~GameScene3D();

	// Inherited via IScene
	virtual void render() override;
	virtual void update() override;
	virtual void onEnter() override;
	virtual void onExit() override;
	virtual void onKeyUP(unsigned char) override;
	virtual void onKeyDown(unsigned char) override;
	virtual void onIdle() override;
	virtual void onSpecialFunc(int) override;
	virtual void onSpecialUpFunc(int) override;
	virtual void reshapeFunc(int, int) override;
};

