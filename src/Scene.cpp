#include "Scene.h"


Scene::Scene(std::string const& path){
    YAML::Node scene=YAML::LoadFile(path);
    for(auto const& obj: scene["gameObjects"]){
        m_objects.emplace(obj["name"].as<std::string>(),obj);
    }

}