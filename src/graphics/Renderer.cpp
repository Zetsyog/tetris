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
	FontGlyph::setDefaultFonts(font24, font48);
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
	SDL_SetRenderDrawColor(get_gRenderer(), 0, 0, 0, 255);
	SDL_RenderCopy(get_gRenderer(), texture->get_gTexture(), NULL, &dest);
}

void Renderer::draw(Texture *texture, int x, int y, int width, int height,
					int srcX, int srcY, int srcWidth, int srcHeight) {
	SDL_Rect dest = {
		.x = x + originX, .y = y + originY, .w = width, .h = height};

	SDL_Rect src = {.x = srcX, .y = srcY, .w = srcWidth, .h = srcHeight};
	SDL_SetRenderDrawColor(get_gRenderer(), 0, 0, 0, 255);

	SDL_RenderCopy(get_gRenderer(), texture->get_gTexture(), &src, &dest);
}

void Renderer::drawTiled(Texture *texture, int x, int y, int width,
						 int height) {
	x += originX;
	y += originY;
	int intWidth  = std::ceil((double)width / (double)texture->getWidth());
	int intHeight = std::ceil((double)height / (double)texture->getHeight());

	for (int i = 0; i < intHeight; i++) {
		int th = i == intHeight - 1 ? (height % texture->getHeight() == 0
										   ? texture->getHeight()
										   : height % texture->getHeight())
									: texture->getHeight();
		for (int j = 0; j < intWidth; j++) {
			if (j == intWidth - 1) {
				int tw = width % texture->getWidth() == 0
							 ? texture->getWidth()
							 : width % texture->getWidth();
				draw(texture, x + j * texture->getWidth(),
					 y + i * texture->getHeight(), tw, th, 0, 0, tw, th);
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
	rect.x = x + originX;
	rect.y = y + originY;
	rect.w = width;
	rect.h = height;

	SDL_SetRenderDrawColor(get_gRenderer(), r, g, b, alpha);
	SDL_RenderDrawRect(get_gRenderer(), &rect);

	SDL_SetRenderDrawColor(get_gRenderer(), 0, 0, 0, 255);
}

void Renderer::drawFilledRect(int x, int y, int width, int height) {
	drawFilledRect(x, y, width, height, 255, 255, 255, 255);
}

void Renderer::drawFilledRect(int x, int y, int width, int height, int r, int g,
							  int b, int alpha) {
	SDL_Rect rect;
	rect.x = x + originX;
	rect.y = y + originY;
	rect.w = width;
	rect.h = height;

	SDL_SetRenderDrawColor(get_gRenderer(), r, g, b, alpha);
	SDL_RenderFillRect(get_gRenderer(), &rect);

	SDL_SetRenderDrawColor(get_gRenderer(), 0, 0, 0, 255);
}

void Renderer::drawFilledRect(int x, int y, int width, int height, int radius) {
	drawFilledRect(x, y, width, height, radius, 255, 255, 255, 255);
}
void Renderer::drawFilledRect(int x, int y, int width, int height, int radius,
							  int r, int g, int b, int alpha) {
	drawFilledCircle(x + radius, y + radius, radius - 1, r, g, b, alpha);
	drawFilledCircle(x + radius, y + height - radius, radius - 1, r, g, b,
					 alpha);
	drawFilledCircle(x + width - radius, y + radius, radius - 1, r, g, b,
					 alpha);
	drawFilledCircle(x + width - radius, y + height - radius, radius - 1, r, g,
					 b, alpha);
	drawFilledRect(x + radius, y, width - 2 * radius, height, r, g, b, alpha);
	drawFilledRect(x, y + radius, width, height - 2 * radius, r, g, b, alpha);
}

void Renderer::drawCircle(int x, int y, int radius, int r, int g, int b,
						  int alpha) {
	int offsetx, offsety, d;

	x += originX;
	y += originY;

	SDL_SetRenderDrawColor(get_gRenderer(), r, g, b, alpha);

	offsetx = 0;
	offsety = radius;
	d		= radius - 1;

	while (offsety >= offsetx) {

		SDL_RenderDrawPoint(get_gRenderer(), x + offsetx, y + offsety);
		SDL_RenderDrawPoint(get_gRenderer(), x + offsety, y + offsetx);
		SDL_RenderDrawPoint(get_gRenderer(), x - offsetx, y + offsety);
		SDL_RenderDrawPoint(get_gRenderer(), x - offsety, y + offsetx);
		SDL_RenderDrawPoint(get_gRenderer(), x + offsetx, y - offsety);
		SDL_RenderDrawPoint(get_gRenderer(), x + offsety, y - offsetx);
		SDL_RenderDrawPoint(get_gRenderer(), x - offsetx, y - offsety);
		SDL_RenderDrawPoint(get_gRenderer(), x - offsety, y - offsetx);

		if (d >= 2 * offsetx) {
			d -= 2 * offsetx + 1;
			offsetx += 1;
		} else if (d < 2 * (radius - offsety)) {
			d += 2 * offsety - 1;
			offsety -= 1;
		} else {
			d += 2 * (offsety - offsetx - 1);
			offsety -= 1;
			offsetx += 1;
		}
	}
}

void Renderer::drawFilledCircle(int x, int y, int radius, int r, int g, int b,
								int alpha) {
	int offsetx, offsety, d;

	x += originX;
	y += originY;

	SDL_SetRenderDrawColor(get_gRenderer(), r, g, b, alpha);

	offsetx = 0;
	offsety = radius;
	d		= radius - 1;

	while (offsety >= offsetx) {
		SDL_RenderDrawLine(get_gRenderer(), x - offsety, y + offsetx,
						   x + offsety, y + offsetx);
		SDL_RenderDrawLine(get_gRenderer(), x - offsetx, y + offsety,
						   x + offsetx, y + offsety);
		SDL_RenderDrawLine(get_gRenderer(), x - offsetx, y - offsety,
						   x + offsetx, y - offsety);
		SDL_RenderDrawLine(get_gRenderer(), x - offsety, y - offsetx,
						   x + offsety, y - offsetx);

		if (d >= 2 * offsetx) {
			d -= 2 * offsetx + 1;
			offsetx += 1;
		} else if (d < 2 * (radius - offsety)) {
			d += 2 * offsety - 1;
			offsety -= 1;
		} else {
			d += 2 * (offsety - offsetx - 1);
			offsety -= 1;
			offsetx += 1;
		}
	}
}

void Renderer::drawText(FontGlyph *glyph, int x, int y) {
	SDL_Rect dest;

	dest.x = x + originX;
	dest.y = y + originY;
	dest.w = glyph->getWidth();
	dest.h = glyph->getHeight();

	SDL_RenderCopy(get_gRenderer(), glyph->get_gTexture(), NULL, &dest);
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
