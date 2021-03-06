#ifndef SCREEN_H
#define SCREEN_H

#include "graphics/Drawable.hpp"
#include "graphics/Renderer.hpp"
#include <vector>

class Screen {
  private:
	std::vector<Drawable *> children;

  public:
	Screen();
	virtual ~Screen();
	virtual void init(Renderer &renderer) = 0;
	virtual void render(double delta, Renderer &renderer);
	virtual void resize(int width, int height);
	virtual void dispose() = 0;

	void add(Drawable *child);
};

class MainScreen : public Screen {
  public:
	MainScreen();
	virtual ~MainScreen();
	virtual void init(Renderer &renderer);
	virtual void render(double delta, Renderer &renderer);
	virtual void resize(int width, int height);
	virtual void dispose();

  private:
	Texture *test;
};

#endif
