#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <vector>
#include <array>

class Texture;

class Renderer {
  private:
	SDL_Renderer *gRenderer;
	SDL_Window *window;
	std::vector<std::array<int, 2>> originStack;
	int originX, originY;

  public:
	Renderer(SDL_Window *window);
	void clear();
	void render();
	void dispose();

	void pushOrigin(int x, int y);
	void popOrigin();

	SDL_Renderer *get_gRenderer();

	void draw(Texture *texture, int x, int y);
	void draw(Texture *texture, int x, int y, int width, int height);
};

#endif