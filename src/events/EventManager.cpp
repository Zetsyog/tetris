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

void EventManager::update() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_KEYDOWN) {
			for (const auto &listener : listeners) {
				listener->keyDown(&event.key);
			}
		} else if (event.type == SDL_KEYUP) {
			for (const auto &listener : listeners) {
				listener->keyUp(&event.key);
			}
		} else if (event.type == SDL_QUIT) {
			app->quit();
		} else if (event.type == SDL_WINDOWEVENT) {
			switch (event.window.event) {
			case SDL_WINDOWEVENT_RESIZED:
				app->resize(event.window.data1, event.window.data2);
			}
		} else if (event.type == SDL_MOUSEBUTTONDOWN) {
			for (const auto &listener : listeners) {
				listener->buttonPressed(&event.button);
			}
		} else if (event.type == SDL_MOUSEBUTTONUP) {
			for (const auto &listener : listeners) {
				listener->buttonReleased(&event.button);
			}
		}
	}
}

void EventListener::keyUp(SDL_KeyboardEvent *event) {
}
void EventListener::keyDown(SDL_KeyboardEvent *event) {
}
void EventListener::buttonPressed(SDL_MouseButtonEvent *event) {
}
void EventListener::buttonReleased(SDL_MouseButtonEvent *event) {
}
