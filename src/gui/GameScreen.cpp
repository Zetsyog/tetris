#include "gui/Screen.hpp"

void GameScreen::init() {
	Screen::init();
	app->getEventManager().addListener(this);
	game = new Game();
	add(game);
}

void GameScreen::render(double delta, Renderer &renderer) {
	Screen::render(delta, renderer);
}

void GameScreen::dispose() {
	Screen::dispose();
	app->getEventManager().removeListener(this);
	delete game;
}

void GameScreen::keyUp(SDL_KeyboardEvent *event) {
	switch (event->keysym.scancode) {
	case SDL_SCANCODE_LEFT:
		game->movePiece(DIRECTION_LEFT);
		break;
	case SDL_SCANCODE_RIGHT:
		game->movePiece(DIRECTION_RIGHT);
		break;
	}
}

void GameScreen::keyDown(SDL_KeyboardEvent *event) {
}
