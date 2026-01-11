#include "Scene.h"
#include <iostream>

Scene::Scene(std::string const& path) {
    YAML::Node scene = YAML::LoadFile(path);

    for (auto const& obj : scene["gameObjects"]) {
        if (!obj["name"]) continue;
        
        std::string name = obj["name"].as<std::string>();
        std::unique_ptr<GameObject> ptr;
        if (name == "flat lumination"){
            ptr = std::make_unique<FlatLum>(obj,this);
        }
        else if (name == "camera") {
            ptr = std::make_unique<Camera>(obj,this);
        } else {

            ptr = std::make_unique<GameObject>(obj, this);
        }


        if (obj["prefab"]) {
            try {
                std::string prefabPath = obj["prefab"].as<std::string>();
                YAML::Node prefab = YAML::LoadFile(prefabPath);
                
                for (auto const& comp : prefab) {
                    if (comp["name"]) {

                        std::string compName = comp["name"].as<std::string>();
                        YAML::Node compData = comp["data"]; 
                        
                        ptr->addComponent(compName, compData);
                    }
                }
            } catch (const std::exception& e) {
                std::cerr << "Failed to load prefab: " << e.what() << std::endl;
            }
        }

        if (obj["components"]) {
            for (auto const& comp : obj["components"]) {
                if (comp["name"]) {
                    ptr->addComponent(comp["name"].as<std::string>(), comp["data"]);
                }
            }
        }


        m_objects.try_emplace(name, std::move(ptr));
    }
}




