#include "App.hpp"
#include <iostream>

namespace {
const int SCREEN_WIDTH	= 800;
const int SCREEN_HEIGHT = 600;
const char *TITLE		= "Tetris";
}

App::App() : currentScreen(nullptr), quit(false), fps(1.0) {
}

int App::start() {
	init();
	loop();
	dispose();
	return 0;
}

void App::init() {
	int rendererFlags, windowFlags;
	rendererFlags = SDL_RENDERER_ACCELERATED;
	windowFlags	  = 0;

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

	renderer = SDL_CreateRenderer(window, -1, rendererFlags);

	if (!renderer) {
		printf("Failed to create renderer: %s\n", SDL_GetError());
		exit(1);
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


		SDL_SetRenderDrawColor(renderer, 96, 128, 255, 255);
		SDL_RenderClear(renderer);

		if (currentScreen != nullptr) {
			currentScreen->update(delta);
			currentScreen->render(renderer);
		}

		SDL_RenderPresent(renderer);

		fps.update();
		SDL_Delay(16);
	}
}

void App::dispose() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}