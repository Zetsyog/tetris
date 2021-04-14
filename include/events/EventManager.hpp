#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include "EventListener.hpp"
#include <SDL2/SDL.h>
#include <vector>

class App;

class EventManager {
  private:
	App *app;
	std::vector<EventListener *> listeners;

  public:
	EventManager(App *app);
	void update();
	void addListener(EventListener *listener);
	void removeListener(EventListener *listener);
};

#endif
