#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "BasicGeometry.h"
#include <vector>

struct Mesh{
    std::vector<Triangle> data;
    bool LoadObjFile(std::string const& path);
};
class Transform{
    public:
        Vector3D m_position={0,0,0};
        Vector3D m_rotation={0,0,0};
        Vector3D m_size={1,1,1};
        Mesh m_mesh;
        

    
};

#endif