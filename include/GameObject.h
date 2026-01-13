#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "Transform.h"
#include "ComponentFactory.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <yaml-cpp/yaml.h>
class Scene;
class Component;

class GameObject{
    public:
        Transform m_transform;
        GameObject(YAML::Node const& obj,Scene* scene);
        virtual ~GameObject() = default;
        void update(Uint32 dt);
        Component* findComponent(std::string const& name);

    protected:
        std::string m_name;
        Component* addComponent(YAML::Node const& data);
        Component* addComponent(std::string const& name, YAML::Node const& data);
        Component* addComponent(std::string const& name);
        std::unordered_map<std::string,std::unique_ptr<Component>> m_components;
        Scene* m_scene=nullptr;



        
        
};
#endif