#pragma once
#include "IScene.h"
class GameEndScene :
	public IScene
{
private:
	static Font* largeFont2D;// ("Font_0.fnt");
	static Font* smallFont3D;// ("Font_0.fnt");
	void drawStrings();
	float scalex = 1.0f, scaley = 1.0f, scalez = 1.0f;
	std::vector<Text> text;
	Texture* logoTexture;
	float lastTime = 0;
	float deltaTime = 0;
	bool reversing = false;

public:
	void appendText(Text &text);
	void renderLogo();
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
	GameEndScene();
	~GameEndScene();
};

