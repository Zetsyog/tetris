#include "gui/Screen.hpp"
#include "graphics/Texture.hpp"

MainScreen::MainScreen() {

}

void MainScreen::init(Renderer &renderer) {
    test = new Texture(renderer, "assets/texture/tetris-logo.png");
}

void MainScreen::render(Renderer &renderer) {
    renderer.draw(test, 10, 100);
}

void MainScreen::update(double delta) {

}

void MainScreen::resize() {
}

void MainScreen::dispose() {
}