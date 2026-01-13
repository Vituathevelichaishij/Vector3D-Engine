#include "Transform.h"
#include <fstream>
#include <sstream>
Transform::Transform(YAML::Node const& obj){
    if(auto transf=obj["transformation"]){
        if(transf["size"]){
            std::vector<float> size=transf["size"].as<std::vector<float>>();
            m_size={size[0],size[1],size[2]};
        }
        if(transf["position"]){
            std::vector<float> position=transf["position"].as<std::vector<float>>();
            m_position={position[0],position[1],position[2]};
        }
        if(transf["rotation"]){
            std::vector<float> rotation=transf["rotation"].as<std::vector<float>>();
            m_rotation={rotation[0],rotation[1],rotation[2]};
        }
    }
    
}










bool Mesh::LoadObjFile(std::string const & path){
    std::ifstream file(path);
    if(!file.is_open()) return false;

    std::vector<Vector3D> verts;
    std::string line;


    while(std::getline(file, line)){
        if(line.empty()) continue;

        std::stringstream ss(line);
        std::string type;
        ss >> type;

        if(type == "v"){
            Vector3D v;
            ss >> v.m_x >> v.m_y >> v.m_z;
            verts.push_back(v);
        }
        else if (type == "f") {
            std::vector<int> f_indices;
            std::string vertexStr;

            while (ss >> vertexStr) {
                std::stringstream vss(vertexStr);
                std::string index;
                if (std::getline(vss, index, '/')) {
                    if (!index.empty()) {
                        f_indices.push_back(std::stoi(index));
                    }
                }
            }

            for (size_t i = 1; i + 1 < f_indices.size(); ++i) {

                int idx0 = f_indices[0] - 1;
                int idx1 = f_indices[i] - 1;
                int idx2 = f_indices[i+1] - 1;

                if (idx0 < verts.size() && idx1 < verts.size() && idx2 < verts.size()) {
                    data.push_back({ verts[idx0], verts[idx1], verts[idx2] });
                }
            }
        }
    }
    return true;
}