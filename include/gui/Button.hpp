#ifndef BUTTON_H
#define BUTTON_H

#include "events/EventListener.hpp"
#include "graphics/FontGlyph.hpp"
#include "gui/Gui.hpp"
#include <iostream>

class ClickListener {
  public:
	virtual void onClick(int buttonId) = 0;
};

class Button : public Gui {
  private:
	int id;
	std::string text;
	int textWidth, textHeight;
	ClickListener *listener;
	FontGlyph *glyph;

  public:
	Button(int id, std::string text, int width, int height);
	virtual ~Button();

	Button *setListener(ClickListener *listener);

	virtual void buttonReleased(SDL_MouseButtonEvent *event);

	virtual void render(Renderer &renderer);
};

#endif
