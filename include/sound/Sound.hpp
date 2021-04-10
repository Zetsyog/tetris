#ifndef SOUND_H
#define SOUND_H

#include <string>

class Sound {
  public:
	Sound(std::string path);
	~Sound();
	void play();
};

#endif