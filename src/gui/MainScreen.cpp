#include "App.hpp"
#include "graphics/Texture.hpp"
#include "gui/Screen.hpp"
#include <vector>

MainScreen::MainScreen() : Screen() {
}

MainScreen::~MainScreen() {
}

void MainScreen::init() {
	app->getEventManager().addListener(this);
	test = new Texture(app->getRenderer(), "assets/texture/tetris-logo.png");

	piece =
		new Piece({{0, 4, 5, 8}, {4, 5, 6, 9}, {2, 6, 10, 5}, {5, 8, 9, 10}});
	add(piece);
}

void MainScreen::keyUp(SDL_KeyboardEvent *event) {
	piece->rotate();
}
void MainScreen::keyDown(SDL_KeyboardEvent *event) {
}

void MainScreen::render(double delta, Renderer &renderer) {
	Screen::render(delta, renderer);
	// renderer.draw(test, 10, 100);
}

void MainScreen::dispose() {
	test->dispose();
	App::getInstance()->getEventManager().removeListener(this);
	delete test;
}