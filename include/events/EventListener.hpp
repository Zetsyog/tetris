#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H

#include <SDL2/SDL.h>

class EventListener {
  public:
	virtual void keyUp(SDL_KeyboardEvent *event);
	virtual void keyDown(SDL_KeyboardEvent *event);
	virtual void buttonPressed(SDL_MouseButtonEvent *event);
	virtual void buttonReleased(SDL_MouseButtonEvent *event);
};

#endif
