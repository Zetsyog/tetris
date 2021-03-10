#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H

#include <SDL2/SDL.h>

class EventListener {
  public:
	virtual void keyUp(SDL_KeyboardEvent *event)   = 0;
	virtual void keyDown(SDL_KeyboardEvent *event) = 0;
};

#endif
