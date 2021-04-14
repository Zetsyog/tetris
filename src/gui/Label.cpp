#include "gui/Label.hpp"

Label::Label(char *text) : text(text) {
}

void Label::render(Renderer &renderer) {
	SDL_Rect size = renderer.drawText(text, x, y);
	setWidth(size.w);
	setHeight(size.h);
}

void Label::update(double delta) {
}
