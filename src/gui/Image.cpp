#include "gui/Image.hpp"

Image::Image(Texture *texture) : texture(texture) {
	setWidth(texture->getWidth());
	setHeight(texture->getHeight());
}

Image::Image(Texture *texture, int width, int height) : texture(texture) {
	setWidth(width);
	setHeight(height);
}

void Image::update(double delta) {
}

void Image::render(Renderer &renderer) {
	renderer.draw(texture, getX(), getY(), getWidth(), getHeight());
}
