#ifndef SCREEN_H
#define SCREEN_H

#include "events/EventListener.hpp"
#include "game/Game.hpp"
#include "graphics/Drawable.hpp"
#include "graphics/Renderer.hpp"
#include "gui/Button.hpp"
#include <vector>

class App;

class Screen : public Drawable {
  private:
	std::vector<Drawable *> children;

  protected:
	App *app;

  public:
	Screen();
	virtual ~Screen();
	virtual void init(App *app);
	virtual void render(Renderer &renderer);
	virtual void update(double delta);
	virtual void resize(int width, int height);

	Drawable *add(Drawable *child);
};

class GameScreen : public Screen, public EventListener {
  private:
	Game *game;

  public:
	virtual ~GameScreen();
	virtual void init(App *app);
	virtual void keyUp(SDL_KeyboardEvent *event);
	virtual void update(double delta);
	virtual void keyDown(SDL_KeyboardEvent *event);
};

class MainMenuScreen : public Screen, public ClickListener {
  private:
	Texture *background;

  public:
	MainMenuScreen();
	virtual ~MainMenuScreen();
	virtual void render(Renderer &renderer);
	virtual void init(App *app);

	virtual void onClick(int buttonId);
};

#include "App.hpp"

#endif
