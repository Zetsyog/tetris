#ifndef FONT_GLYPH_H
#define FONT_GLYPH_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

class FontGlyph {
  private:
	static TTF_Font *defaultFont, *defaultBigFont;
	std::string text;
	Uint8 r, g, b, alpha;
	int width, height;
	TTF_Font *font;
	SDL_Texture *texture;

  public:
	FontGlyph(std::string text);
	FontGlyph(std::string text, bool big);
	FontGlyph(std::string text, TTF_Font *font);
	virtual ~FontGlyph();

	const char *getText() const;
	void setText(std::string text);
	SDL_Texture *get_gTexture() const;
	int getWidth() const;
	int getHeight() const;

	void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 alpha);

	static void setDefaultFonts(TTF_Font *small, TTF_Font *large);
};

#endif
