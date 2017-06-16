#include "SoundManager.h"



SoundManager::SoundManager()
{
	//Init Soundmanager
	soundEngine = createIrrKlangDevice();
}


SoundManager::~SoundManager()
{
	soundEngine->drop();
}

//playsound till sound is over.
void SoundManager::playSound(Sound sound)
{
	if (soundEngine->play2D(sound.file.c_str()) != 0)
	{
		cout << "Error: Could not play " << sound.name << endl;
		return;
	}
}

//stop all playing sound in the whole project
void SoundManager::stopSound()
{
	soundEngine->stopAllSounds();
}
