#include "FlatLum.h"


FlatLum::FlatLum(YAML::Node const& obj,Scene* scene) : Lumination(obj, scene){
    m_lightDir={0,0,1};
    m_lightDir.rotate(m_transform.m_rotation);
    
}




