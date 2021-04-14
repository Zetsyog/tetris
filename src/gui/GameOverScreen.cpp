#include "gui/Button.hpp"
#include "gui/Image.hpp"
#include "gui/Screen.hpp"

GameOverScreen::GameOverScreen(int score) : score(score) {
}

GameOverScreen::~GameOverScreen() {
}

void GameOverScreen::init(App *app) {
	Screen::init(app);
	add((new Image(app->getResourceManager().get("texture:logo"), 1000 / 2,
				   694 / 2))
			->centerX());

	add((new Button(0, "Return to menu", 300, 100))
			->setListener(this)
			->center()
			->offsetY(200));

	background = app->getResourceManager().get("texture:background");
}

void GameOverScreen::render(Renderer &renderer) {
	renderer.drawTiled(background, 0, 0, app->getWindowWidth(),
					   app->getWindowHeight());
	Screen::render(renderer);
}

void GameOverScreen::onClick(int buttonId) {
	switch (buttonId) {
	case 0:
		app->setCurrentScreen(new MainMenuScreen());
		break;

	default:
		break;
	}
}
