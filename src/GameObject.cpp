#include "GameObject.h"
#include <iostream>
GameObject::GameObject(YAML::Node const& obj,Scene* scene) : m_scene(scene), m_name(){

    m_name=obj["name"].as<std::string>();


    if(obj["mesh"]){
    
        m_transform.m_mesh.LoadObjFile(obj["mesh"].as<std::string>());
    }
    
    if(auto transf=obj["transformation"]){

        if(transf["size"]){
            std::vector<float> size=transf["size"].as<std::vector<float>>();
            m_transform.m_size={size[0],size[1],size[2]};
        }
        if(transf["position"]){
            std::vector<float> position=transf["position"].as<std::vector<float>>();
            m_transform.m_position={position[0],position[1],position[2]};
        }
        if(transf["rotation"]){
            std::vector<float> rotation=transf["rotation"].as<std::vector<float>>();
            m_transform.m_rotation={rotation[0],rotation[1],rotation[2]};
        }
    }
}

GameObject::GameObject(){}













void GameObject::update(Uint32 dt){
    for(auto& c:m_components){
        c.second->update(dt);
    }
}



std::unique_ptr<Component> GameObject::addComponent(std::string const& name, YAML::Node const& data){
    auto comp = ComponentFactory::init().create(name);


    if(!comp) return nullptr;
    comp->owner=this;
    comp->init(data);
    m_components.insert({name,std::move(comp)});

    return comp;
}

std::unique_ptr<Component> GameObject::addComponent(std::string const& name){
    auto comp = ComponentFactory::init().create(name);
    
    if(!comp) return nullptr;
    comp->owner=this;
    m_components.insert({name,std::move(comp)});
    return comp;

}