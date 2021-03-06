#include "App.hpp"
#include <SDL2/SDL_image.h>
#include <iostream>

namespace {
const int SCREEN_WIDTH	= 800;
const int SCREEN_HEIGHT = 600;
const char *TITLE		= "Tetris";
} // namespace

App::App() : currentScreen(nullptr), quit(false), fps(1.0) {
}

int App::start() {
	loop();
	dispose();
	return 0;
}

void App::init() {
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

	renderer = new Renderer(window);

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		printf("SDL_image could not initialize! SDL_image Error: %s\n",
			   IMG_GetError());
		exit(EXIT_FAILURE);
	}
}

void App::pollEvents() {
	SDL_Event event;
	while (!quit && SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			quit = true;
			break;
		default:
			break;
		}
	}
}

void App::loop() {
	Uint64 prev, now = SDL_GetPerformanceCounter();
	double delta;

	quit = false;
	while (!quit) {
		// const Uint8 *state = SDL_GetKeyboardState(NULL);
		// keyboard(state);
		// quit |= (state[SDL_SCANCODE_ESCAPE] != 0);
		pollEvents();

		prev  = now;
		now	  = SDL_GetPerformanceCounter();
		delta = (double)((now - prev) / (double)SDL_GetPerformanceFrequency());

		renderer->clear();

		if (currentScreen != nullptr) {
			currentScreen->update(delta);
			currentScreen->render(*renderer);
		}

		renderer->render();

		fps.update();
		SDL_Delay(16);
	}
}

void App::setCurrentScreen(Screen *screen) {
	if(currentScreen != nullptr) {
		currentScreen->dispose();
		delete currentScreen;
	}
	screen->init(*renderer);
	currentScreen = screen;
}

void App::dispose() {
	renderer->dispose();
	SDL_DestroyWindow(window);
	SDL_Quit();
}