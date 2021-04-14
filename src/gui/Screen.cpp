#include "gui/Screen.hpp"
#include "App.hpp"
#include <iostream>

Screen::Screen() : app(nullptr) {
}

void Screen::init(App *app) {
	this->app = app;
}

void Screen::update(double delta) {
	for (const auto &child : children) {
		child->update(delta);
	}
}

void Screen::render(Renderer &renderer) {
	for (const auto &child : children) {
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

Drawable *Screen::add(Drawable *child) {
	child->resize(app->getWindowWidth(), app->getWindowHeight());
	children.push_back(child);
	return child;
}

Screen::~Screen() {
	for (const auto &child : children) {
		delete (child);
	}
}
