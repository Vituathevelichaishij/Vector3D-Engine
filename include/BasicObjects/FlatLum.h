#ifndef FLATILUM_H
#define FLATILUM_H
#include "GameObject.h"
#include "Lumination.h"
class FlatLum : public Lumination{
    public:
        FlatLum(YAML::Node const& obj,Scene* scene);
        FlatLum() =default;
        Vector3D m_lightDir;
    private:
};

#endif