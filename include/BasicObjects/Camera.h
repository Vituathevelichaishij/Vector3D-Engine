#ifndef CAMERA_H
#define CAMERA_H
#include "GameObject.h"
class Camera : public GameObject{
    public:
        Camera(YAML::Node const& obj,Scene* scene);
};

#endif