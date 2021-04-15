#include "resources/Music.hpp"

Music::Music(std::string path) : path(path) {
	music = Mix_LoadMUS(path.c_str());
	if (!music) {
		printf("Mix_LoadMUS(\"%s\"): %s\n", path.c_str(), Mix_GetError());
	}
}

int Music::play() {
	int ret = Mix_PlayMusic(music, -1);
	Mix_ResumeMusic();
	return ret;
}

void Music::stop() {
	Mix_PauseMusic();
	Mix_RewindMusic();
}

Music::~Music() {
	Mix_FreeMusic(music);
}