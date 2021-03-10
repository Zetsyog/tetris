#ifndef SCREEN_H
#define SCREEN_H

#include "events/EventListener.hpp"
#include "game/Game.hpp"
#include "graphics/Drawable.hpp"
#include "graphics/Renderer.hpp"
#include <vector>

class App;

class Screen {
  private:
	std::vector<Drawable *> children;

  protected:
	App *app;

  public:
	Screen();
	virtual ~Screen();
	virtual void init();
	virtual void render(double delta, Renderer &renderer);
	virtual void resize(int width, int height);
	virtual void dispose();

	Drawable *add(Drawable *child);
};

class MainScreen : public Screen, public EventListener {
  public:
	MainScreen();
	virtual ~MainScreen();
	virtual void init();
	virtual void render(double delta, Renderer &renderer);
	virtual void dispose();
	virtual void keyUp(SDL_KeyboardEvent *event);
	virtual void keyDown(SDL_KeyboardEvent *event);

  private:
	Texture *test;
	Piece *piece;
};

class GameScreen : public Screen, public EventListener {
  private:
	Game *game;

  public:
	virtual void init();
	virtual void render(double delta, Renderer &renderer);
	virtual void dispose();
	virtual void keyUp(SDL_KeyboardEvent *event);
	virtual void keyDown(SDL_KeyboardEvent *event);
};

#include "App.hpp"

#endif
