#include "gui/Screen.hpp"
#include <iostream>

Screen::Screen() : children() {
}

Screen::~Screen() {
}

void Screen::init(Renderer &renderer) {
	for (const auto &child : children) {
		child->init(renderer);
	}
}

void Screen::dispose() {
	for (const auto &child : children) {
		child->dispose();
	}
}

void Screen::render(double delta, Renderer &renderer) {
	for (const auto &child : children) {
		child->update(delta);
		if (child->isVisible()) {
		    child->render(renderer);
		}
	}
}

void Screen::resize(int width, int height) {
	for (const auto &child : children) {
		child->resize(width, height);
	}
}
