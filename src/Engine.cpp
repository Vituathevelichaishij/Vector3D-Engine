#include "Engine.h"
#include "InputHandler.h"
extern void RegisterAllComponents();

Engine::Engine() : m_window(m_settings), m_renderer(m_window, m_settings){}

void Engine::start(){
    RegisterAllComponents();
    m_scene=Scene("scene/scene1.yaml");
    int countedFrames = 0;
    m_timer.start();
    
    
    
    while(!m_quit){
        InputHandler::pullEvents();



        if(InputHandler::keyEventofType(SDL_QUIT)){
            m_quit = true;
        }
	    
        for(auto& o : m_scene.m_objects){
            o.second->update(0);
        }
        m_renderer.render(m_scene);
        std::cout<<countedFrames / ( m_timer.getTicks() / 1000.f )<<std::endl; 
        ++countedFrames;
    }
    
}