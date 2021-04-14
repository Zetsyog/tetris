#ifndef RENDERER_H
#define RENDERER_H

#include "graphics/FontGlyph.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <array>
#include <vector>

#define FONT_PATH "assets/font/default.ttf"

class Texture;
class App;

class Renderer {
  private:
	App *app;
	SDL_Renderer *gRenderer;
	SDL_Window *window;
	std::vector<std::array<int, 2>> originStack;
	int originX, originY;
	TTF_Font *font24;
	TTF_Font *font48;

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
	void draw(Texture *texture, int x, int y, int width, int height, int srcX,
			  int srcY, int srcWidth, int srcHeight);

	void drawRect(int x, int y, int width, int height);
	void drawRect(int x, int y, int width, int height, int r, int g, int b,
				  int alpha);

	void drawFilledRect(int x, int y, int width, int height);
	void drawFilledRect(int x, int y, int width, int height, int r, int g,
						int b, int alpha);

	void drawFilledRect(int x, int y, int width, int height, int radius);
	void drawFilledRect(int x, int y, int width, int height, int radius, int r,
						int g, int b, int alpha);

	void drawCircle(int x, int y, int radius, int r, int g, int b, int alpha);
	void drawFilledCircle(int x, int y, int radius, int r, int g, int b,
						  int alpha);

	void drawTiled(Texture *texture, int x, int y, int width, int height);

	void drawText(FontGlyph *glyph, int x, int y);
};

#endif