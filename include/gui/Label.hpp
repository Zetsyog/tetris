#ifndef LABEL_H
#define LABEL_H

#include "gui/Gui.hpp"

class Label : public Gui {
  private:
	int id;
	std::string text;
	FontGlyph *glyph;

  public:
	Label(std::string text);
	Label(std::string text, bool big);

	virtual void render(Renderer &renderer);
};

#endif
