#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "BasicGeometry.h"
#include <vector>
class Transform{
    public:
        Vector3D m_position={0,0,0};
        Vector3D m_rotation={0,0,0};
        std::vector<Triangle> m_mesh;

    
};

#endif