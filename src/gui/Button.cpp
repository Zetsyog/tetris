#include "gui/Button.hpp"
#include "App.hpp"

Button::Button(int id, std::string text, int width, int height) : id(id) {
	this->text = text;
	glyph	   = new FontGlyph(text);
	setWidth(width);
	setHeight(height);
}

void Button::render(Renderer &renderer) {
	renderer.drawRect(x, y, width, height);

	renderer.drawText(glyph, x + getWidth() / 2 - glyph->getWidth() / 2,
					  y + getHeight() / 2 - glyph->getHeight() / 2);
}

Button *Button::setListener(ClickListener *listener) {
	this->listener = listener;
	return this;
}

void Button::buttonReleased(SDL_MouseButtonEvent *event) {
	if (listener == nullptr)
		return;
	if (event->x >= x && event->x <= x + width && event->y >= y &&
		event->y <= y + height) {
		listener->onClick(id);
	}
}

void Button::update(double delta) {
}

Button::~Button() {
	delete glyph;
}
