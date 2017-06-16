#pragma once
#include "IScene.h"
#include "Font.h"
#include <vector>
#include "Text.h"
#include "Texture.h"

class MainMenuScene :
	public IScene
{

private:
	static Font* largeFont2D;// ("font_72.fnt");
	static Font* smallFont2D;// ("Font_0.fnt");
	static Font* largeFont3D;// ("font_72.fnt");
	static Font* smallFont3D;// ("Font_0.fnt");
	void drawStrings();
	float scalex = 1.0f, scaley = 1.0f, scalez = 1.0f;
	string startString = "Press any key to start!";
	string mainString = "Main Menu";
	std::vector<Text> text;
	Texture logoTexture = Texture("logo.png");
	float lastTime = 0;
	float deltaTime = 0;
	static IScene* gameInstance;
	bool reversing = false;


public:
	MainMenuScene();
	~MainMenuScene();
	
	// Inherited via IScene
	void appendText(Text &text);
	void renderLogo();
	virtual void render3D() override;
	virtual void render2D() override;
	virtual void onEnter() override;
	virtual void onExit() override;
	virtual void update() override;
	virtual void onIdle() override;
	virtual void onKeyUP(unsigned char) override;
	virtual void onKeyDown(unsigned char) override;
	virtual void onSpecialFunc(int) override;
	virtual void onSpecialUpFunc(int) override;
	virtual void reshapeFunc(int, int) override;

};

