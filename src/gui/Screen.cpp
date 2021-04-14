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

Gui *Screen::add(Gui *child) {
	child->resize(app->getWindowWidth(), app->getWindowHeight());
	children.push_back(child);
	return child;
}

Screen::~Screen() {
	for (const auto &child : children) {
		delete (child);
	}
}

void Screen::keyUp(SDL_KeyboardEvent *event) {
	for (const auto &child : children) {
		child->keyUp(event);
	}
}

void Screen::keyDown(SDL_KeyboardEvent *event) {
	for (const auto &child : children) {
		child->keyDown(event);
	}
}

void Screen::buttonPressed(SDL_MouseButtonEvent *event) {
	for (const auto &child : children) {
		child->buttonPressed(event);
	}
}

void Screen::buttonReleased(SDL_MouseButtonEvent *event) {
	for (const auto &child : children) {
		child->buttonReleased(event);
	}
}
