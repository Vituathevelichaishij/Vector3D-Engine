#include "GameObject.h"

GameObject::GameObject(YAML::Node const& obj){
    m_name=obj["name"].as<std::string>();



    for(auto const& triangle : obj["mesh"]){
        auto tri=triangle.as<std::vector<std::vector<float>>>();
        Vector3D a={tri[0][0],tri[0][1],tri[0][2]};
        Vector3D b={tri[1][0],tri[1][1],tri[1][2]};
        Vector3D c={tri[2][0],tri[2][1],tri[2][2]};
        m_transform.m_mesh.emplace_back(a,b,c);
    }
}

