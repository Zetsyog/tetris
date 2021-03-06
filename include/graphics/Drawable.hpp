#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "graphics/Renderer.hpp"
#include <SDL2/SDL.h>

class Drawable {
  private:
	bool visible;

  public:
	Drawable();
	virtual ~Drawable();
	virtual void init(Renderer &renderer)	   = 0;
	virtual void update(double delta)		   = 0;
	virtual void render(Renderer &renderer)	   = 0;
	virtual void resize(int width, int height) = 0;
	virtual void dispose()					   = 0;
	virtual void setVisible(bool visible);
	virtual bool isVisible();
};

#endif
