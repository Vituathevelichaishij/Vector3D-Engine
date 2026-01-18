#include "r.h"
#include "GameObject.h"
#include "ComponentFactory.h"
#include <cmath>
void register_r()
{ComponentFactory::init().registerComponent("r", []() {return std::make_unique<r>();   });}


void r::update(Uint32 dT)
{   
    Vector3D a={20,0,0};
    Vector3D angles={0,0,0};
    float speed=0.003;
    angles.m_y=angles.m_y+speed*dT;
    a.rotate(angles);
    owner->m_transform.m_position=a;
}



 void r::start(){};
 void r::init(YAML::Node const& data){};