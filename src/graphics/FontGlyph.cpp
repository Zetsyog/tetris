#include "graphics/FontGlyph.hpp"
#include "App.hpp"

TTF_Font *FontGlyph::defaultFont;
TTF_Font *FontGlyph::defaultBigFont;

FontGlyph::FontGlyph(std::string text)
	: texture(nullptr), font(FontGlyph::defaultFont), r(255), g(255), b(255),
	  alpha(255) {
	setText(text);
}

FontGlyph::FontGlyph(std::string text, bool big)
	: texture(nullptr), r(255), g(255), b(255), alpha(255) {
	if (big) {
		font = FontGlyph::defaultBigFont;
	} else {
		font = FontGlyph::defaultFont;
	}
	setText(text);
}

FontGlyph::FontGlyph(std::string text, TTF_Font *font)
	: texture(nullptr), r(255), g(255), b(255), alpha(255) {
	setText(text);
}

FontGlyph::~FontGlyph() {
	if (texture != nullptr) {
		SDL_DestroyTexture(texture);
	}
}

const char *FontGlyph::getText() const {
	return text.c_str();
}

void FontGlyph::setText(std::string text) {
	this->text = text;
	if (texture != nullptr) {
		SDL_DestroyTexture(texture);
	}
	SDL_Color color		 = {r, g, b, alpha};
	SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), color);
	texture				 = SDL_CreateTextureFromSurface(
		 App::get()->getRenderer().get_gRenderer(), surface);
	width  = surface->w;
	height = surface->h;
	SDL_FreeSurface(surface);
}

void FontGlyph::setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 alpha) {
	this->r		= r;
	this->g		= g;
	this->b		= b;
	this->alpha = alpha;
}

int FontGlyph::getWidth() const {
	return width;
}

int FontGlyph::getHeight() const {
	return height;
}

SDL_Texture *FontGlyph::get_gTexture() const {
	return texture;
}

void FontGlyph::setDefaultFonts(TTF_Font *small, TTF_Font *large) {
	FontGlyph::defaultFont	  = small;
	FontGlyph::defaultBigFont = large;
}