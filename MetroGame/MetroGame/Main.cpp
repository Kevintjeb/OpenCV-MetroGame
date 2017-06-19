#include "system.h"
#include "Main.h"

#include "SoundManager.h"

//extern "C" {
//	_declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
//}

int main(int argc, char **argv)
{

	////play sound
	//first a sound
	//create in the whole project 1 soundmanager.
	//use playSound() methode

	Sound soundTrack = Sound("soundTrack", "sound\\Background.mp3");
	SoundManager sm = SoundManager();
	sm.playSound(soundTrack);


	mg_system::init(argc, argv);
	mg_system::start();
}

