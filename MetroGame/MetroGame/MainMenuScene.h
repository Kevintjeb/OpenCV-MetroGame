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

