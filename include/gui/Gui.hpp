#ifndef GUI_H
#define GUI_H

#include <SDL2/SDL.h>

class Gui {
  public:
	virtual void init()							= 0;
	virtual void update(double delta)			= 0;
	virtual void render(SDL_Renderer *renderer) = 0;
	virtual void resize()						= 0;
	virtual void dispose()						= 0;
};

#endif
