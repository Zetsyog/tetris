#ifndef SOUND_H
#define SOUND_H

#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>



class Sound {
	private: 
		bool isInit;
		Mix_Chunk *snd;
	public:
		Sound(std::string path);
		~Sound();
    	void play(int i, bool looped);
		bool init();
		bool on;
};

#endif