#include "Engine.h"


Engine::Engine() : m_window(m_settings), m_renderer(m_window, m_settings){}


void Engine::start(){
    m_scene=Scene("scene/scene1.yaml");
    m_scene.m_objects.find("cube")->second.m_transform.m_position.m_z=600;

    while(!m_quit){
        m_scene.m_objects.find("cube")->second.m_transform.m_rotation.m_x+=1;


        while(SDL_PollEvent(&m_event) != 0){
            if(m_event.type == SDL_QUIT){
                m_quit = true;
            }
	    }
        m_renderer.render(m_scene);
    }
}