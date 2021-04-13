#include "App.hpp"
#include <iostream>

namespace {
const int SCREEN_WIDTH	= 800;
const int SCREEN_HEIGHT = 800;
const char *TITLE		= "Tetris";
} // namespace

App::App() : currentScreen(nullptr), running(true), fps(1.0) {
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

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

	window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED,
							  SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
							  SCREEN_HEIGHT, windowFlags);

	if (!window) {
		printf("Failed to open %d x %d window: %s\n", SCREEN_WIDTH,
			   SCREEN_HEIGHT, SDL_GetError());
		exit(1);
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

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
		// const Uint8 *state = SDL_GetKeyboardState(NULL);
		// keyboard(state);
		// quit |= (state[SDL_SCANCODE_ESCAPE] != 0);

		prev  = now;
		now	  = SDL_GetPerformanceCounter();
		delta = (double)((now - prev) / (double)SDL_GetPerformanceFrequency());

		eventManager->update();

		renderer->clear();

		if (currentScreen != nullptr) {
			currentScreen->render(delta, *renderer);
		}

		renderer->render();

		fps.update();
		SDL_Delay(32);
	}
}

void App::setCurrentScreen(Screen *screen) {
	if (currentScreen != nullptr) {
		delete currentScreen;
	}
	screen->init(this);
	currentScreen = screen;
}

EventManager &App::getEventManager() {
	return *eventManager;
}

SDL_Window *App::get_glWindow() {
	return window;
}

App::~App() {
	delete renderer;
	delete resourceManager;
	SDL_DestroyWindow(window);
	SDL_Quit();
}

Renderer &App::getRenderer() {
	return *renderer;
}

ResourceManager &App::getResourceManager() {
	return *resourceManager;
}