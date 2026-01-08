#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "Transform.h"
#include <string>
#include <vector>
#include <yaml-cpp/yaml.h>
class GameObject{
    public:
        GameObject(YAML::Node const& obj);
        std::string m_name;
        Transform m_transform;
};
#endif