#ifndef APP_H
#define APP_H

#include "events/EventManager.hpp"
#include "graphics/Renderer.hpp"
#include "gui/Screen.hpp"
#include "util/FPSCounter.hpp"
#include <SDL2/SDL.h>

class App {
  private:
	Screen *currentScreen;
	Renderer *renderer;
	EventManager eventManager;
	SDL_Window *window;
	bool running;
	FPSCounter fps;

	void loop();
	void dispose();

  protected:
	App();
	static App *instance;

  public:
	App(App &other) = delete;
	void init();
	int start();
	void quit();
	void setCurrentScreen(Screen *screen);
	EventManager &getEventManager();
	Renderer &getRenderer();

	static App *getInstance();
};

#endif