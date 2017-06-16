#pragma once
#include <iostream>
#include <string>
#include <windows.h>
#include <vector>

#include "irrklang\include\irrKlang.h"
#include "Sound.h"

using namespace std;
using namespace irrklang;

class SoundManager
{
private:
	ISoundEngine* soundEngine = nullptr;
public:
	SoundManager();
	~SoundManager();
	void playSound(Sound);
	void stopSound();
};

