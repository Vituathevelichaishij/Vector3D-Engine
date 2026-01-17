#include "InputHandler.h"
#include <iostream>
SDL_Event InputHandler::m_e;
std::vector<SDL_Event> InputHandler::all_events={};

void InputHandler::pullEvents(){
    all_events.clear();
    while(SDL_PollEvent(&m_e)){
        all_events.push_back(m_e);
	}

};


bool InputHandler::keyEventofType(SDL_EventType key){
    for(auto& e : all_events){
        if(e.type==key) return true;
    }
    return false;
}


bool InputHandler::keyIsPressed(SDL_KeyCode key){
    for(auto& e : all_events){
        if(e.key.keysym.sym==key) return true;
    }
    return false;
}