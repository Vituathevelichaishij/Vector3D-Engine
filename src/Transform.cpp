#include "Transform.h"
#include <fstream>
#include <sstream>
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
        else if(type == "f"){
            std::vector<int> f_indices;
            std::string vertexStr;
            
            while(ss >> vertexStr) {

                std::stringstream vss(vertexStr);
                std::string index;
                std::getline(vss, index, '/'); 
                f_indices.push_back(std::stoi(index));
            }


            if(f_indices.size() >= 3) {
                data.push_back({
                    verts[f_indices[0] - 1],
                    verts[f_indices[1] - 1],
                    verts[f_indices[2] - 1]
                });
            }
        }
    }
    return true;
}