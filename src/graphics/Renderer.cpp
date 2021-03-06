#include "graphics/Renderer.hpp"
#include "graphics/Texture.hpp"

Renderer::Renderer(SDL_Window *window): window(window) {
    gRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!gRenderer) {
		printf("Failed to create renderer: %s\n", SDL_GetError());
		exit(1);
	}
}

SDL_Renderer *Renderer::get_gRenderer() {
    return gRenderer;
}

void Renderer::draw(Texture *texture, int x, int y) {
    SDL_Rect dest;
	
	dest.x = x;
	dest.y = y;
	SDL_QueryTexture(texture->get_gTexture(), NULL, NULL, &dest.w, &dest.h);
	
	SDL_RenderCopy(get_gRenderer(), texture->get_gTexture(), NULL, &dest);
}

void Renderer::clear() {
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
	SDL_RenderClear(gRenderer);
}

void Renderer::render() {
    SDL_RenderPresent(gRenderer);
}

void Renderer::dispose() {
    SDL_DestroyRenderer(gRenderer);
}
