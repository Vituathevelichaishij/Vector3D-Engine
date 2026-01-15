#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "BasicGeometry.h"
#include <vector>
#include <yaml-cpp/yaml.h>
struct Polygon{
    Polygon(Triangle const& tr);
    Triangle tri;
};



struct Mesh{
    std::vector<Polygon> data;
    bool Light=true;
    bool LoadObjFile(std::string const& path);
};
class Transform{
    public:
        Transform(YAML::Node const& obj);
        Vector3D m_position={0,0,0};
        Vector3D m_rotation={0,0,0};
        Vector3D m_size={1,1,1};
        Mesh m_mesh;
        

    
};

#endif