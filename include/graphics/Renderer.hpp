#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>

class Texture;

class Renderer {
  public:
	Renderer(SDL_Window *window);
	void clear();
	void render();
	void dispose();

	SDL_Renderer *get_gRenderer();

	void draw(Texture *texture, int x, int y);
	void draw(Texture *texture, int x, int y, int width, int height);

  private:
	SDL_Renderer *gRenderer;
	SDL_Window *window;
};

#endif
