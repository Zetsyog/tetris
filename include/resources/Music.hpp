#ifndef SOUND_H
#define SOUND_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string>

class Music {
  private:
	Mix_Music *music;
	std::string path;

  public:
	Music(std::string path);
	~Music();
	int play();
	void stop();
};

#endif