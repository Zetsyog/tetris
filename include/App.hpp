#ifndef APP_H
#define APP_H

#include "gui/Screen.hpp"
#include <SDL2/SDL.h>

class App {
    private:
        Screen *currentScreen;
        SDL_Renderer *renderer;
	    SDL_Window *window;
        bool quit;

    private:
        void init();
        void loop();
        void pollEvents();
        void dispose();
    
    public:
        App();
        int start();
};

#endif