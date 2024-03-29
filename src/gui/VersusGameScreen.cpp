#include "gui/Screen.hpp"

static bool down = false;

void VersusGameScreen::init(App *app) {
	Screen::init(app);
	background = app->getResourceManager().get("texture:background");

	game   = new Game(*app);
	aiGame = new AIGame(*app);
	game->start();
	aiGame->start();
	add(game->center()->offsetX(-360));
	add(aiGame->center()->offsetX(360));

	music = app->getResourceManager().getMusic("music:main");
	music->play();
}

VersusGameScreen::~VersusGameScreen() {
	music->stop();
}

void VersusGameScreen::render(Renderer &renderer) {
	renderer.drawTiled(background, 0, 0, app->getWindowWidth(),
					   app->getWindowHeight());
	Screen::render(renderer);
}

void VersusGameScreen::update(double delta) {
	SDL_PumpEvents();
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_DOWN] && !down) {
		game->setSoftDrop(true);
		down = true;
	} else if (!state[SDL_SCANCODE_DOWN] && down) {
		game->setSoftDrop(false);
		down = false;
	}

	for (int i = 0; i < game->getLineFilled(); i++) {
		aiGame->addLine();
	}
	for (int i = 0; i < aiGame->getLineFilled(); i++) {
		game->addLine();
	}
	Screen::update(delta);

	if (game->isDone() || aiGame->isDone()) {
		app->setCurrentScreen(new GameOverScreen(game->getScore()));
	}
}

void VersusGameScreen::keyUp(SDL_KeyboardEvent *event) {
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

void VersusGameScreen::keyDown(SDL_KeyboardEvent *event) {
}
