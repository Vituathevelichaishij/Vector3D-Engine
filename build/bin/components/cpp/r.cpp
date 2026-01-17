#include "r.h"
#include "GameObject.h"
#include "ComponentFactory.h"
void register_r()
{ComponentFactory::init().registerComponent("r", []() {return std::make_unique<r>();   });}


void r::update(Uint32 dT)
{
    owner->m_transform.m_rotation.m_y+=1;
}



 void r::start(){};
 void r::init(YAML::Node const& data){};