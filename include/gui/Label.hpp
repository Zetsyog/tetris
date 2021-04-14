#ifndef LABEL_H
#define LABEL_H

#include "gui/Gui.hpp"

class Label : public Gui {
  private:
	char *text;

  public:
	Label(char *text);

	virtual void render(Renderer &renderer);
	virtual void update(double delta);
};

#endif
