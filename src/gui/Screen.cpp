#include "gui/Screen.hpp"
#include "App.hpp"
#include <iostream>

Screen::Screen() : children(), app(nullptr) {
}

void Screen::init(App *app) {
	this->app = app;
}

Screen::~Screen() {
	for (const auto &child : children) {
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