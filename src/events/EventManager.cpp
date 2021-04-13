#include "events/EventManager.hpp"
#include "App.hpp"
#include <iostream>

using namespace std;

EventManager::EventManager(App *app) : listeners(), app(app) {
}

void EventManager::addListener(EventListener *listener) {
	listeners.push_back(listener);
}

void EventManager::removeListener(EventListener *listener) {
	for (std::vector<EventListener *>::iterator it = listeners.begin();
		 it != listeners.end(); ++it) {
		if (*it == listener) {
			listeners.erase(it);
			break;
		}
	}
}

void EventManager::keyUp(SDL_KeyboardEvent *event) {
	for (const auto &listener : listeners) {
		listener->keyUp(event);
	}
}

void EventManager::keyDown(SDL_KeyboardEvent *event) {
	for (const auto &listener : listeners) {
		listener->keyDown(event);
	}
}

void EventManager::update() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN:
			keyDown(&event.key);
			break;
		case SDL_KEYUP:
			keyUp(&event.key);
			break;
		case SDL_QUIT:
			app->quit();
			break;
		}
	}
}