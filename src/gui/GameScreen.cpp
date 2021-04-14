#include "gui/Screen.hpp"

void GameScreen::init(App *app) {
	Screen::init(app);
	app->getEventManager().addListener(this);
	game = new Game(*app);
	add(game);
	game->start();
}

void GameScreen::render(double delta, Renderer &renderer) {
	Screen::render(delta, renderer);
}

GameScreen::~GameScreen() {
	app->getEventManager().removeListener(this);
	delete game;
}

void GameScreen::keyUp(SDL_KeyboardEvent *event) {
	switch (event->keysym.scancode) {
	case SDL_SCANCODE_LEFT:
		game->action(ACTION_MOVE_LEFT);
		break;
	case SDL_SCANCODE_RIGHT:
		game->action(ACTION_MOVE_RIGHT);
		break;
	case SDL_SCANCODE_UP:
		game->action(ACTION_ROTATE);
		break;
	case SDL_SCANCODE_DOWN:
		game->setSpeed(1);
		break;
	}
}

void GameScreen::keyDown(SDL_KeyboardEvent *event) {
	switch (event->keysym.scancode) {
	case SDL_SCANCODE_DOWN:
		game->setSpeed(8);
		break;

	default:
		break;
	}
}