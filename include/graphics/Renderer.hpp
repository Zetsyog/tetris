#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <array>
#include <vector>

class Texture;
class App;

class Renderer {
  private:
	App *app;
	SDL_Renderer *gRenderer;
	SDL_Window *window;
	std::vector<std::array<int, 2>> originStack;
	int originX, originY;

  public:
	Renderer(App *app);
	~Renderer();
	void clear();
	void render();

	void pushOrigin(int x, int y);
	void popOrigin();

	SDL_Renderer *get_gRenderer();

	void draw(Texture *texture, int x, int y);
	void draw(Texture *texture, int x, int y, int width, int height);
};

#endif