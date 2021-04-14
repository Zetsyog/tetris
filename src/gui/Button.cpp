#include "gui/Button.hpp"
#include "App.hpp"

Button::Button(int id, std::string text, int width, int height) : id(id) {
	this->text = text;
	setWidth(width);
	setHeight(height);
	App::get()->getEventManager().addListener(this);
}

void Button::render(Renderer &renderer) {
	SDL_Rect size = renderer.getBigTextSize(text.c_str());
	textWidth	  = size.w;
	textHeight	  = size.h;
	renderer.drawBigText(text.c_str(), x + width / 2 - textWidth / 2,
						 y + height / 2 - textHeight / 2);
	renderer.drawRect(x, y, width, height);
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
	App::get()->getEventManager().removeListener(this);
}
