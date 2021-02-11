

#include <SDL2/SDL.h>
#include "util/FPSCounter.hpp"
#include <iostream>

FPSCounter::FPSCounter(float interval): frames(0), current(0), interval(interval) {
	last_time = SDL_GetTicks();
}

void FPSCounter::update() {
	frames++;
	if(last_time < SDL_GetTicks() - interval * 1000) {
		last_time = SDL_GetTicks();
		current = frames;
		frames = 0;
		// std::cout << getAverage() << std::endl;
	}
}


int FPSCounter::getAverage() {
	return current;
}