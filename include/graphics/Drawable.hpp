#ifndef GUI_H
#define GUI_H

#include "graphics/Renderer.hpp"
#include <SDL2/SDL.h>

class Drawable {
  public:
	virtual void init(Renderer &renderer)	= 0;
	virtual void update(double delta)		= 0;
	virtual void render(Renderer &renderer) = 0;
	virtual void resize()					= 0;
	virtual void dispose()					= 0;
};

#endif
