#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

const char *TITLE = "Hello World SDL2 + TTF";
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

using namespace std;

int main(int argc, char **argv) {
	// The window we'll be rendering to
	SDL_Window *gWindow = NULL;

	// The window renderer
	SDL_Renderer *gRenderer = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

	// Current displayed texture
	bool quit = false;
	// Create window
	gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
							   SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
							   SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (gWindow == NULL) {
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
	} else {
		// Create renderer for window
		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
		if (gRenderer == NULL) {
			printf("Renderer could not be created! SDL Error: %s\n",
				   SDL_GetError());
		} else {
			// Initialize renderer color
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		}
	}
	TTF_Init();

	TTF_Font *verdanaFont = TTF_OpenFont("assets/font/default.ttf", 40);
	SDL_Color textColor	  = {0, 0, 0, 255};
	SDL_Surface *textSurface =
		TTF_RenderText_Solid(verdanaFont, "Hello World", textColor);
	SDL_Texture *textTexture =
		SDL_CreateTextureFromSurface(gRenderer, textSurface);

	SDL_Rect textRect;
	textRect.x = textSurface->w * 0.5;
	textRect.y = textSurface->h * 0.5;
	textRect.w = textSurface->w;
	textRect.h = textSurface->h;

	SDL_FreeSurface(textSurface);

	SDL_Surface *loadedSurface = IMG_Load("assets/texture/block/red.png");
	SDL_Texture *gTexture;
	if (loadedSurface == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n",
			   "assets/texture/block/red.png", IMG_GetError());
	} else {
		// Create texture from surface pixels
		gTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (gTexture == NULL) {
			printf("Unable to create texture from %s! SDL Error: %s\n",
				   "assets/texture/block/red.png", SDL_GetError());
		}

		// Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	SDL_Event e;
	// While application is running
	while (!quit) {
		// Handle events on queue
		while (SDL_PollEvent(&e) != 0) {
			// User requests quit
			if (e.type == SDL_QUIT) {
				quit = true;
			}
		}
		SDL_RenderClear(gRenderer);

		SDL_Rect rect;
		rect.x = 100;
		rect.y = 100;
		SDL_QueryTexture(gTexture, NULL, NULL, &rect.w, &rect.h);
		SDL_RenderCopy(gRenderer, gTexture, NULL, &rect);
		// Render texture to screen
		SDL_RenderCopy(gRenderer, textTexture, NULL, &textRect);

		// Update screen
		SDL_RenderPresent(gRenderer);
		SDL_Delay(100);
	}
	// Destroy window
	SDL_DestroyTexture(textTexture);
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow	  = NULL;
	gRenderer = NULL;

	TTF_Quit();
	// Quit SDL subsystems
	SDL_Quit();
}