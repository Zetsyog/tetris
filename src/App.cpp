#include "App.hpp"
#include <SDL2/SDL_mixer.h>
#include <iostream>

namespace {
const int SCREEN_WIDTH	= 1450;
const int SCREEN_HEIGHT = 1000;
const char *TITLE		= "Tetris";
} // namespace

App *App::instance = nullptr;

App::App()
	: currentScreen(nullptr), nextScreen(nullptr), running(true), fps(1.0),
	  windowWidth(SCREEN_WIDTH), windowHeight(SCREEN_HEIGHT) {
	initSDL();
	renderer		= new Renderer(this);
	resourceManager = new ResourceManager(this);
	eventManager	= new EventManager(this);
}

int App::start() {
	loop();
	return 0;
}

void App::quit() {
	running = false;
}

void App::initSDL() {
	int windowFlags;
	windowFlags = 0;
	windowFlags |= SDL_WINDOW_SHOWN;
	windowFlags |= SDL_WINDOW_RESIZABLE;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

	if (TTF_Init() == -1) {
		printf("TTF_Init: %s\n", TTF_GetError());
		exit(1);
	}

	int flags	= MIX_INIT_OGG | MIX_INIT_MOD;
	int initted = Mix_Init(flags);
	if (initted & flags != flags) {
		printf("Mix_Init: Failed to init required ogg and mod support!\n");
		printf("Mix_Init: %s\n", Mix_GetError());
		// handle error
	}

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
		std::cerr << "Error while initializing SDL" << std::endl;
	}

	window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED,
							  SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
							  SCREEN_HEIGHT, windowFlags);

	if (!window) {
		printf("Failed to open %d x %d window: %s\n", SCREEN_WIDTH,
			   SCREEN_HEIGHT, SDL_GetError());
		exit(1);
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		printf("SDL_image could not initialize! SDL_image Error: %s\n",
			   IMG_GetError());
		exit(EXIT_FAILURE);
	}
}

void App::loop() {
	Uint64 prev, now = SDL_GetPerformanceCounter();
	double delta;
	running = true;

	while (running) {
		prev  = now;
		now	  = SDL_GetPerformanceCounter();
		delta = (double)((now - prev) / (double)SDL_GetPerformanceFrequency());

		if (nextScreen != nullptr) {
			if (currentScreen != nullptr) {
				delete currentScreen;
			}
			nextScreen->init(this);
			currentScreen = nextScreen;
			nextScreen	  = nullptr;
		}

		eventManager->update();

		renderer->clear();
		if (currentScreen != nullptr) {
			currentScreen->update(delta);
			currentScreen->render(*renderer);
		}
		renderer->render();

		fps.update();
		SDL_Delay(32);
	}
}

int App::getWindowWidth() const {
	return windowWidth;
}

int App::getWindowHeight() const {
	return windowHeight;
}

void App::resize(int width, int height) {
	windowWidth	 = width;
	windowHeight = height;
	if (currentScreen != nullptr) {
		currentScreen->resize(width, height);
	}
}

void App::setCurrentScreen(Screen *screen) {
	if (nextScreen != nullptr) {
		delete nextScreen;
	}
	nextScreen = screen;
}

EventManager &App::getEventManager() {
	return *eventManager;
}

SDL_Window *App::get_glWindow() {
	return window;
}

App::~App() {
	delete eventManager;
	if (currentScreen != nullptr) {
		delete currentScreen;
	}
	delete resourceManager;
	delete renderer;
	SDL_DestroyWindow(window);
	TTF_Quit();
	IMG_Quit();
	Mix_CloseAudio();
	SDL_Quit();
}

Renderer &App::getRenderer() {
	return *renderer;
}

ResourceManager &App::getResourceManager() {
	return *resourceManager;
}

Screen &App::getCurrentScreen() {
	return *currentScreen;
}

App *App::create() {
	instance = new App();
	return instance;
}

App *App::get() {
	return instance;
}

void App::destroy() {
	delete instance;
}
