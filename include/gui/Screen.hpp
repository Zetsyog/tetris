#ifndef SCREEN_H
#define SCREEN_H

#include "Gui.hpp"

class Screen : public Gui {
  public:
	Screen();
	virtual void init();
	virtual void update(double delta);
	virtual void render(SDL_Renderer *renderer);
	virtual void resize();
	virtual void dispose();
};

#endif
