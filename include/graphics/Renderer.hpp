#ifndef RENDERER_H
#define RENDERER_H

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

	void drawTiled(Texture *texture, int x, int y, int width, int height);

	SDL_Rect drawText(const char *text, int x, int y);
	SDL_Rect drawBigText(const char *text, int x, int y);
	SDL_Rect getTextSize(const char *text);
	SDL_Rect getBigTextSize(const char *text);
};

#endif