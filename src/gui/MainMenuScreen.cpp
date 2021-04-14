#include "gui/Button.hpp"
#include "gui/Image.hpp"
#include "gui/Screen.hpp"

MainMenuScreen::MainMenuScreen() {
}

MainMenuScreen::~MainMenuScreen() {
}

void MainMenuScreen::init(App *app) {
	Screen::init(app);
	add((new Image(app->getResourceManager().get("texture:logo"), 1000 / 2,
				   694 / 2))
			->centerX());

	add((new Button(0, "Play", 300, 100))->setListener(this)->center());

	background = app->getResourceManager().get("texture:background");
}

void MainMenuScreen::render(Renderer &renderer) {
	renderer.drawTiled(background, 0, 0, app->getWindowWidth(),
					   app->getWindowHeight());
	Screen::render(renderer);
}

void MainMenuScreen::onClick(int buttonId) {
	switch (buttonId) {
	case 0:
		app->setCurrentScreen(new GameScreen());
		break;

	default:
		break;
	}
}
