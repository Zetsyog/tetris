#include "graphics/Texture.hpp"
#include <SDL2/SDL_image.h>

Texture::Texture(Renderer &renderer, std::string path) : path(path) {
	// Load image at specified path
	SDL_Surface *loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(),
			   IMG_GetError());
	} else {
		// Create texture from surface pixels
		gTexture = SDL_CreateTextureFromSurface(renderer.get_gRenderer(),
												loadedSurface);
		if (gTexture == NULL) {
			printf("Unable to create texture from %s! SDL Error: %s\n",
				   path.c_str(), SDL_GetError());
		}

		SDL_QueryTexture(gTexture, NULL, NULL, &width, &height);

		// Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}
}

int Texture::getWidth() const {
	return width;
}

int Texture::getHeight() const {
	return height;
}

Texture::~Texture() {
	SDL_DestroyTexture(get_gTexture());
}

SDL_Texture *Texture::get_gTexture() {
	return gTexture;
}