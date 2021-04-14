#include "graphics/Renderer.hpp"
#include "App.hpp"
#include "graphics/Texture.hpp"

Renderer::Renderer(App *app)
	: window(window), originX(0), originY(0), originStack(), app(app) {
	gRenderer =
		SDL_CreateRenderer(app->get_glWindow(), -1, SDL_RENDERER_ACCELERATED);

	if (!gRenderer) {
		printf("Failed to create renderer: %s\n", SDL_GetError());
		exit(1);
	}

	font24 = TTF_OpenFont(FONT_PATH, 24);
	font48 = TTF_OpenFont(FONT_PATH, 48);
}

SDL_Renderer *Renderer::get_gRenderer() {
	return gRenderer;
}

void Renderer::draw(Texture *texture, int x, int y) {
	draw(texture, x, y, texture->getWidth(), texture->getHeight());
}

void Renderer::draw(Texture *texture, int x, int y, int width, int height) {
	SDL_Rect dest;

	dest.x = x + originX;
	dest.y = y + originY;
	dest.w = width;
	dest.h = height;
	SDL_RenderCopy(get_gRenderer(), texture->get_gTexture(), NULL, &dest);
}

void Renderer::draw(Texture *texture, int x, int y, int width, int height,
					int srcX, int srcY, int srcWidth, int srcHeight) {
	SDL_Rect dest = {
		.x = x + originX, .y = y + originY, .w = width, .h = height};

	SDL_Rect src = {.x = srcX, .y = srcY, .w = srcWidth, .h = srcHeight};

	SDL_RenderCopy(get_gRenderer(), texture->get_gTexture(), &src, &dest);
}

void Renderer::drawTiled(Texture *texture, int x, int y, int width,
						 int height) {
	int intWidth  = std::ceil((double)width / (double)texture->getWidth());
	int intHeight = std::ceil((double)height / (double)texture->getHeight());

	for (int i = 0; i < intHeight; i++) {
		int th = i == intHeight - 1 ? height % texture->getHeight()
									: texture->getHeight();
		for (int j = 0; j < intWidth; j++) {
			if (j == intWidth - 1) {
				draw(texture, x + j * texture->getWidth(),
					 y + i * texture->getHeight(), width % texture->getWidth(),
					 th, 0, 0, width % texture->getWidth(), th);
			} else {
				draw(texture, x + j * texture->getWidth(),
					 y + i * texture->getHeight(), texture->getWidth(), th, 0,
					 0, texture->getWidth(), th);
			}
		}
	}
}

void Renderer::drawRect(int x, int y, int width, int height) {
	drawRect(x, y, width, height, 255, 255, 255, 255);
}

void Renderer::drawRect(int x, int y, int width, int height, int r, int g,
						int b, int alpha) {
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = width;
	rect.h = height;

	SDL_SetRenderDrawColor(get_gRenderer(), r, g, b, alpha);
	SDL_RenderDrawRect(get_gRenderer(), &rect);

	SDL_SetRenderDrawColor(get_gRenderer(), 0, 0, 0, 255);
}

SDL_Rect Renderer::drawText(const char *text, int x, int y) {
	SDL_Color color		 = {255, 255, 255};
	SDL_Surface *surface = TTF_RenderText_Solid(font24, text, color);
	SDL_Texture *texture =
		SDL_CreateTextureFromSurface(get_gRenderer(), surface);

	SDL_Rect dest;

	dest.x = x + originX;
	dest.y = y + originY;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
	SDL_RenderCopy(get_gRenderer(), texture, NULL, &dest);

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
	return dest;
}

SDL_Rect Renderer::getTextSize(const char *text) {
	SDL_Color color		 = {255, 255, 255};
	SDL_Surface *surface = TTF_RenderText_Solid(font24, text, color);
	SDL_Texture *texture =
		SDL_CreateTextureFromSurface(get_gRenderer(), surface);

	SDL_Rect dest;

	dest.x = 0;
	dest.y = 0;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
	return dest;
}

SDL_Rect Renderer::drawBigText(const char *text, int x, int y) {
	SDL_Color color		 = {255, 255, 255};
	SDL_Surface *surface = TTF_RenderText_Solid(font48, text, color);
	SDL_Texture *texture =
		SDL_CreateTextureFromSurface(get_gRenderer(), surface);

	SDL_Rect dest;

	dest.x = x + originX;
	dest.y = y + originY;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
	SDL_RenderCopy(get_gRenderer(), texture, NULL, &dest);

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
	return dest;
}

SDL_Rect Renderer::getBigTextSize(const char *text) {
	SDL_Color color		 = {255, 255, 255};
	SDL_Surface *surface = TTF_RenderText_Solid(font48, text, color);
	SDL_Texture *texture =
		SDL_CreateTextureFromSurface(get_gRenderer(), surface);

	SDL_Rect dest;

	dest.x = 0;
	dest.y = 0;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
	return dest;
}

void Renderer::pushOrigin(int x, int y) {
	originStack.push_back({x, y});
	originX += x;
	originY += y;
}

void Renderer::popOrigin() {
	originX -= originStack.back()[0];
	originY -= originStack.back()[1];
	originStack.pop_back();
}

void Renderer::clear() {
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
	SDL_RenderClear(gRenderer);
}

void Renderer::render() {
	SDL_RenderPresent(gRenderer);
}

Renderer::~Renderer() {
	TTF_CloseFont(font24);
	TTF_CloseFont(font48);
	SDL_DestroyRenderer(gRenderer);
}
