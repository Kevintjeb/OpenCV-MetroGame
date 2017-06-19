#pragma once
#include <string>

class Sound
{
private:

public:
	std::string name;
	std::string file;

	Sound(std::string, std::string);
	~Sound();
};

