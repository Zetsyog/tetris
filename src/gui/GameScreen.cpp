#include "gui/Screen.hpp"

static bool down = false;

void GameScreen::init(App *app) {
	Screen::init(app);
	background = app->getResourceManager().get("texture:background");

	game = new Game(*app);
	add(game->center());
	game->start();

	music = app->getResourceManager().getMusic("music:main");
	music->play();
}
GameScreen::~GameScreen() {
	music->stop();
}

void GameScreen::render(Renderer &renderer) {
	renderer.drawTiled(background, 0, 0, app->getWindowWidth(),
					   app->getWindowHeight());
	Screen::render(renderer);
}

void GameScreen::update(double delta) {
	SDL_PumpEvents();
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_DOWN] && !down) {
		game->setSoftDrop(true);
		down = true;
	} else if (!state[SDL_SCANCODE_DOWN] && down) {
		game->setSoftDrop(false);
		down = false;
	}
	Screen::update(delta);

	if (game->isDone()) {
		app->setCurrentScreen(new GameOverScreen(game->getScore()));
	}
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
	case SDL_SCANCODE_ESCAPE:
		app->setCurrentScreen(new MainMenuScreen());
		break;
	}
}

void GameScreen::keyDown(SDL_KeyboardEvent *event) {
}
