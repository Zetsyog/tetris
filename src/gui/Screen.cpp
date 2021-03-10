#include "gui/Screen.hpp"
#include "App.hpp"
#include <iostream>

Screen::Screen() : children() {
}

Screen::~Screen() {
}

void Screen::init(App &app) {
	for (const auto &child : children) {
		child->init(app.getRenderer());
	}
}

void Screen::dispose() {
	for (const auto &child : children) {
		child->dispose();
		delete (child);
	}
}

Drawable *Screen::add(Drawable *child) {
	children.push_back(child);
	return child;
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
