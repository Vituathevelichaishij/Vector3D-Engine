#ifndef SCENE_H
#define SCENE_H
#include <unordered_map>
#include <string>
#include "GameObject.h"
#include <yaml-cpp/yaml.h>
class Scene{
    public:
        Scene()= default;
        Scene(std::string const& path);
        std::string sceneName;
        std::unordered_map<std::string, GameObject> m_objects;
};



#endif