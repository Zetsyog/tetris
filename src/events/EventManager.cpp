#include "events/EventManager.hpp"
#include "App.hpp"
#include <algorithm>
#include <iostream>

using namespace std;

EventManager::EventManager(App *app) : app(app) {
}

void EventManager::update() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_KEYDOWN) {
			app->getCurrentScreen().keyDown(&event.key);
		} else if (event.type == SDL_KEYUP) {
			app->getCurrentScreen().keyUp(&event.key);
		} else if (event.type == SDL_QUIT) {
			app->quit();
		} else if (event.type == SDL_WINDOWEVENT) {
			switch (event.window.event) {
			case SDL_WINDOWEVENT_RESIZED:
				app->resize(event.window.data1, event.window.data2);
			}
		} else if (event.type == SDL_MOUSEBUTTONDOWN) {
			app->getCurrentScreen().buttonPressed(&event.button);
		} else if (event.type == SDL_MOUSEBUTTONUP) {
			app->getCurrentScreen().buttonReleased(&event.button);
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
