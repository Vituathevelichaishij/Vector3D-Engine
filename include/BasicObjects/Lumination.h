#ifndef LUMINATION_H
#define LUMINATION_H
#include "GameObject.h"
class Lumination : public GameObject{
    public:
        Lumination() =default;
        Lumination(YAML::Node const& obj,Scene* scene):GameObject(obj,scene){}
    private:
        
};

#endif