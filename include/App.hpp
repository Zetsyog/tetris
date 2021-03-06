#ifndef APP_H
#define APP_H

#include <SDL2/SDL.h>
#include "gui/Screen.hpp"
#include "util/FPSCounter.hpp"
#include "graphics/Renderer.hpp"

class App {
  private:
	Screen *currentScreen;
	Renderer *renderer;
	SDL_Window *window;
	bool quit;
	FPSCounter fps;

  private:
	void loop();
	void pollEvents();
	void dispose();

  public:
	App();
	void init();
	int start();
	void setCurrentScreen(Screen *screen);
};

#endif