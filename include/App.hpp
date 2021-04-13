#ifndef APP_H
#define APP_H

#include "events/EventManager.hpp"
#include "graphics/Renderer.hpp"
#include "gui/Screen.hpp"
#include "resources/ResourceManager.hpp"
#include "util/FPSCounter.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class App {
  private:
	ResourceManager *resourceManager;
	Screen *currentScreen;
	Renderer *renderer;
	EventManager *eventManager;
	SDL_Window *window;
	bool running;
	FPSCounter fps;

	void loop();
	void initSDL();

  public:
	App();
	App(App &other) = delete;
	~App();
	int start();
	void quit();
	void setCurrentScreen(Screen *screen);
	EventManager &getEventManager();
	Renderer &getRenderer();
	ResourceManager &getResourceManager();
	SDL_Window *get_glWindow();
};

#endif