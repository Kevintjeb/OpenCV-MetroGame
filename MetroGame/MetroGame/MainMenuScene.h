#pragma once
#include "IScene.h"
#include "Font.h"
class MainMenuScene :
	public IScene
{

private:
	static Font* largeFont;// ("font_72.fnt");
	static Font* smallFont;// ("Font_0.fnt");
	string startString = "Press any key to start!";
	string mainString = "Main Menu";

public:
	MainMenuScene();
	~MainMenuScene();
	
	// Inherited via IScene
	void render3D() override;
	void render2D() override;
	void onEnter() override;
	void onExit() override;
	void update() override;
	void onIdle() override;
	void onKeyUP(unsigned char) override;
	void onKeyDown(unsigned char) override;
	void onSpecialFunc(int) override;
	void onSpecialUpFunc(int) override;
	void reshapeFunc(int, int) override;
};

