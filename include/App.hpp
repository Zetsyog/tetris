#ifndef APP_H
#define APP_H

#include "events/EventManager.hpp"
#include "graphics/Renderer.hpp"
#include "gui/Screen.hpp"
#include "resources/ResourceManager.hpp"
#include "util/FPSCounter.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class App {
  private:
	static App *instance;

	ResourceManager *resourceManager;
	Screen *currentScreen;
	Renderer *renderer;
	EventManager *eventManager;
	SDL_Window *window;
	int windowWidth, windowHeight;
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
	void resize(int width, int height);

	int getWindowWidth() const;
	int getWindowHeight() const;

	EventManager &getEventManager();
	Renderer &getRenderer();
	ResourceManager &getResourceManager();
	SDL_Window *get_glWindow();

	static App *create();
	static App *get();
	static void destroy();
};

#endif