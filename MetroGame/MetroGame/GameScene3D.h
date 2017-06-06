#pragma once
#include "IScene.h"
#include "Font.h"
class GameScene3D :
	public IScene
{
private:
	static Font* largeFont3D;
	string time;
	struct {
		float seconds = 0;
		int minutes = 0;
	}Time;
	void prepareTime(float deltaTime);

public:
	GameScene3D();
	~GameScene3D();

	// Inherited via IScene
	virtual void render2D() override;
	virtual void render3D() override;
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

