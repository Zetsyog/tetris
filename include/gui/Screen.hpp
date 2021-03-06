#ifndef SCREEN_H
#define SCREEN_H

#include "graphics/Renderer.hpp"
#include "graphics/Drawable.hpp"

class Screen : public Drawable {
  public:
	virtual void init(Renderer &renderer)	= 0;
	virtual void update(double delta)		= 0;
	virtual void render(Renderer &renderer) = 0;
	virtual void resize()					= 0;
	virtual void dispose()					= 0;
};

class MainScreen : public Screen {
  public:
	MainScreen();
	virtual void init(Renderer &renderer);
	virtual void update(double delta);
	virtual void render(Renderer &renderer);
	virtual void resize();
	virtual void dispose();

  private:
	Texture *test;
};

#endif
