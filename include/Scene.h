#ifndef SCENE_H
#define SCENE_H
#include <unordered_map>
#include <string>
#include "GameObject.h"
#include <yaml-cpp/yaml.h>
#include "BasicObjects.h"

class Scene{
    public:
        Scene() =default;
        Scene(std::string const& path);
        std::string m_sceneName;

        std::unordered_map<std::string, std::unique_ptr<GameObject>> m_objects;




        template<typename T>
        T* find(){
            for(auto &o : m_objects){
                if(T* ptr=dynamic_cast<T*>(o.second.get())){
                    return ptr;
                }
            }
            return nullptr;
        }


        template<typename T>
        const T* find() const{
            for(auto &o : m_objects){
                if(const T* ptr=dynamic_cast<T*>(o.second.get())){
                    return ptr;
                }
            }
            return nullptr;
        }
};



#endif