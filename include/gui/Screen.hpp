#ifndef SCREEN_H
#define SCREEN_H

#include "events/EventListener.hpp"
#include "game/AIGame.hpp"
#include "game/Game.hpp"
#include "graphics/Drawable.hpp"
#include "graphics/Renderer.hpp"
#include "gui/Button.hpp"
#include "resources/Music.hpp"
#include <vector>

class App;

class Screen : public Drawable, public EventListener {
  private:
	std::vector<Gui *> children;

  protected:
	App *app;

  public:
	Screen();
	virtual ~Screen();
	virtual void init(App *app);
	virtual void render(Renderer &renderer);
	virtual void update(double delta);
	virtual void resize(int width, int height);

	virtual void keyUp(SDL_KeyboardEvent *event);
	virtual void keyDown(SDL_KeyboardEvent *event);
	virtual void buttonPressed(SDL_MouseButtonEvent *event);
	virtual void buttonReleased(SDL_MouseButtonEvent *event);

	Gui *add(Gui *child);
};

class GameScreen : public Screen {
  private:
	Game *game;
	Music *music;
	Texture *background;

  public:
	virtual ~GameScreen();
	virtual void init(App *app);
	virtual void keyUp(SDL_KeyboardEvent *event);
	virtual void update(double delta);
	virtual void render(Renderer &renderer);
	virtual void keyDown(SDL_KeyboardEvent *event);
};

class VersusGameScreen : public Screen {
  private:
	Game *game;
	AIGame *aiGame;
	Texture *background;

  public:
	virtual ~VersusGameScreen();
	virtual void init(App *app);
	virtual void keyUp(SDL_KeyboardEvent *event);
	virtual void update(double delta);
	virtual void render(Renderer &renderer);
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

class GameOverScreen : public Screen, public ClickListener {
  private:
	Texture *background;
	int score;

  public:
	GameOverScreen(int score);
	virtual ~GameOverScreen();
	virtual void render(Renderer &renderer);
	virtual void init(App *app);

	virtual void onClick(int buttonId);
};

#include "App.hpp"

#endif
