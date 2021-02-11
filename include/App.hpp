#ifndef APP_H
#define APP_H

#include <SDL2/SDL.h>
#include "gui/Screen.hpp"
#include "util/FPSCounter.hpp"

class App {
  private:
	Screen *currentScreen;
	SDL_Renderer *renderer;
	SDL_Window *window;
	bool quit;
	FPSCounter fps;

  private:
	void init();
	void loop();
	void pollEvents();
	void dispose();

  public:
	App();
	int start();
};

#endif