#ifndef TEXTURE_H
#define TEXTURE_H

#include "graphics/Renderer.hpp"
#include <SDL2/SDL.h>
#include <iostream>

class Texture {
  public:
	Texture(Renderer &renderer, std::string path);
	void dispose();
	SDL_Texture *get_gTexture();

  private:
	std::string path;
	SDL_Texture *gTexture;
};

#endif