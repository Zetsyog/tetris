#include "gui/Screen.hpp"

static bool down = false;

void GameScreen::init(App *app) {
	Screen::init(app);
	app->getEventManager().addListener(this);
	game = new Game(*app);
	add(game);
	game->start();

	music = app->getResourceManager().getMusic("music:main");
	music->play();
}

GameScreen::~GameScreen() {
	app->getEventManager().removeListener(this);
	music->stop();
	delete game;
}

void GameScreen::update(double delta) {
	SDL_PumpEvents();
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_DOWN] && !down) {
		game->setSpeed(16);
		down = true;
	} else if (!state[SDL_SCANCODE_DOWN] && down) {
		game->setSpeed(1);
		down = false;
	}
	Screen::update(delta);
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
	}
}

void GameScreen::keyDown(SDL_KeyboardEvent *event) {
}
