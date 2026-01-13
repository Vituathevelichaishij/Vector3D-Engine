#include "rotation.h"
#include "GameObject.h"
#include "ComponentFactory.h"
void register_rotation()
{ComponentFactory::init().registerComponent("rotation", []() {return std::make_unique<rotation>();   });}


 void rotation::update(Uint32 dT){
    owner->m_transform.m_rotation.m_y+=2;
 }
 void rotation::start(){};
 void rotation::init(YAML::Node const& data){};