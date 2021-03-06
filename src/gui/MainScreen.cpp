#include "gui/Screen.hpp"
#include "graphics/Texture.hpp"

MainScreen::MainScreen(): Screen() {

}

MainScreen::~MainScreen() {
}

void MainScreen::init(Renderer &renderer) {
    test = new Texture(renderer, "assets/texture/tetris-logo.png");
}

void MainScreen::render(double delta, Renderer &renderer) {
    Screen::render(delta, renderer);
    renderer.draw(test, 10, 100);
}

void MainScreen::resize(int width, int height) {
}

void MainScreen::dispose() {
}