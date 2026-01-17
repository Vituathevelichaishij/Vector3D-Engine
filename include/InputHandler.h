#pragma once
#include <vector>
#include <SDL2/SDL.h>
class  InputHandler{
    public:
        void static pullEvents();
        bool  static keyEventofType(SDL_EventType key);
        bool  static keyIsPressed(SDL_KeyCode key);

    private:
        static SDL_Event m_e;
        static std::vector<SDL_Event> all_events;

};