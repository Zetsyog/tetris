#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include "EventListener.hpp"
#include <SDL2/SDL.h>
#include <vector>

class EventManager {
  private:
	std::vector<EventListener *> listeners;
	void keyUp(SDL_KeyboardEvent *event);
	void keyDown(SDL_KeyboardEvent *event);

  public:
	EventManager();
	void update();
	void addListener(EventListener *listener);
	void removeListener(EventListener *listener);
};

#endif