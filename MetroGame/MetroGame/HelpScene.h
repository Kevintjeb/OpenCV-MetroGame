#pragma once
#include "IScene.h"
#include "Font.h"

class HelpScene :
	public IScene
{

private:
	static Font *largeFont2D;
	Texture* logoTexture;
	const string sceneString = "Inside help screen!";
	float deltaTime = 0;
	float lastTime = 0;
	float textY = 0, textX = 0;
	IScene* backScene;
	bool reversing = false;
	
public:
	void setBackScene(IScene* back);
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
	HelpScene();
	~HelpScene();
	void renderLogo();
	IScene* getBackScene();
};

