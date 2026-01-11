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
        GameObject(YAML::Node const& obj,Scene* scene);
        virtual ~GameObject() = default;
        void update(Uint32 dt);
        std::unique_ptr<Component> addComponent(std::string const& name, YAML::Node const& data);
        std::unique_ptr<Component> addComponent(std::string const& name);
        std::string m_name;
        Transform m_transform;
        std::unordered_map<std::string,std::unique_ptr<Component>> m_components;


        template<typename T>
        T* find(){
            for(auto &o : m_components){
                if(T* ptr=dynamic_cast<T*>(o.second.get())){
                    return ptr;
                }
            }
            return nullptr;
        }


        template<typename T>
        const T* find() const{
            for(auto &o : m_components){
                if(const T* ptr=dynamic_cast<T*>(o.second.get())){
                    return ptr;
                }
            }
            return nullptr;
        }
    protected:
        GameObject();
    private:
        Scene* m_scene=nullptr;
        
};
#endif