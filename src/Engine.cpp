#include "Engine.h"
extern void RegisterAllComponents();

Engine::Engine() : m_window(m_settings), m_renderer(m_window, m_settings){}

void Engine::start(){
    RegisterAllComponents();
    m_scene=Scene("scene/scene1.yaml");


    
    
    
    while(!m_quit){



        while(SDL_PollEvent(&m_event) != 0){
            if(m_event.type == SDL_QUIT){
                m_quit = true;
            }
	    }
        for(auto& o : m_scene.m_objects){
            o.second->update(0);
        }
        m_renderer.render(m_scene);
    }
    
}