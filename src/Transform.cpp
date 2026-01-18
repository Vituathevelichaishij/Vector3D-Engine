#include "Transform.h"
#include <fstream>
#include <sstream>

Polygon::Polygon(Triangle3D const& tr):tri(tr){};
Polygon::Polygon(Triangle3D const& tr,float lum):tri(tr), m_lum(lum){}
Polygon::Polygon(Triangle3D const& tr,Triangle2D const& textCor):tri(tr), text(textCor){};


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
        if(transf["light"]){
            m_light=transf["light"].as<bool>();
        }
    }
    
}



Mesh::~Mesh(){
    if(sprite){
        SDL_FreeSurface(sprite);
        sprite=nullptr;
    }
}


std::vector<int> parseOBJIndex(const std::string& vertexStr) {
    std::vector<int> indices(3, -1);
    
    size_t start = 0;
    size_t slash1 = vertexStr.find('/', start);
    

    if (slash1 != std::string::npos && slash1 > start) {
        std::string vStr = vertexStr.substr(start, slash1 - start);
        if (!vStr.empty()) {
            try {
                indices[0] = std::stoi(vStr);
            } catch (...) {
                indices[0] = -1;
            }
        }
    } else if (slash1 == std::string::npos) {
        // Нет слэшей - только индекс вершины
        if (!vertexStr.empty()) {
            try {
                indices[0] = std::stoi(vertexStr);
            } catch (...) {
                indices[0] = -1;
            }
        }
        return indices;
    }
    

    start = slash1 + 1;
    size_t slash2 = vertexStr.find('/', start);
    
    if (slash2 != std::string::npos && slash2 > start) {
        std::string tStr = vertexStr.substr(start, slash2 - start);
        if (!tStr.empty()) {
            try {
                indices[1] = std::stoi(tStr);
            } catch (...) {
                indices[1] = -1;
            }
        }
    } else if (slash2 == std::string::npos && start < vertexStr.size()) {

        std::string tStr = vertexStr.substr(start);
        if (!tStr.empty()) {
            try {
                indices[1] = std::stoi(tStr);
            } catch (...) {
                indices[1] = -1;
            }
        }
        return indices;
    }
    

    start = slash2 + 1;
    if (start < vertexStr.size()) {
        std::string nStr = vertexStr.substr(start);
        if (!nStr.empty()) {
            try {
                indices[2] = std::stoi(nStr);
            } catch (...) {
                indices[2] = -1;
            }
        }
    }
    
    return indices;
}



bool Mesh::LoadObjFile(std::string const & path){
    std::ifstream file(path);
    if(!file.is_open()) return false;

    std::vector<Vector3D> verts;
    std::vector<Vector2D> texCoords;  
    std::string line;

    while(std::getline(file, line)){
        if(line.empty() || line[0] == '#') continue;

        std::stringstream ss(line);
        std::string type;
        ss >> type;

        if(type == "v"){  
            Vector3D v;
            ss >> v.m_x >> v.m_y >> v.m_z;
            
            
            float dummy;
            while(ss >> dummy) {} 
            
            verts.push_back(v);
        }
        else if(type == "vt"){  
            Vector2D vt;
            ss >> vt.m_u >> vt.m_v;
            
           
            float w;
            if (ss >> w) {
                
            }
            
            texCoords.push_back(vt);
        }
        else if (type == "f") {
            std::vector<std::string> faceTokens;
            std::string token;
            

            while (ss >> token) {
                faceTokens.push_back(token);
            }
            

            if (faceTokens.size() >= 3) {

                std::vector<int> baseIndices = parseOBJIndex(faceTokens[0]);
                bool hasTexture = (baseIndices.size() > 1 && baseIndices[1] != -1);
                

                std::vector<std::vector<int>> allIndices;
                for (const auto& token : faceTokens) {
                    allIndices.push_back(parseOBJIndex(token));
                }
                

                for (size_t i = 1; i + 1 < allIndices.size(); ++i) {
                    const auto& idx0 = allIndices[0];
                    const auto& idx1 = allIndices[i];
                    const auto& idx2 = allIndices[i + 1];
                    

                    if (idx0.size() > 0 && idx0[0] != -1 &&
                        idx1.size() > 0 && idx1[0] != -1 &&
                        idx2.size() > 0 && idx2[0] != -1) {
                        
                        int v0 = idx0[0] - 1;
                        int v1 = idx1[0] - 1;
                        int v2 = idx2[0] - 1;
                        

                        if (v0 >= 0 && v0 < static_cast<int>(verts.size()) &&
                            v1 >= 0 && v1 < static_cast<int>(verts.size()) &&
                            v2 >= 0 && v2 < static_cast<int>(verts.size())) {
                            
                            Triangle3D tri3d = { verts[v0], verts[v1], verts[v2] };
                            Triangle2D tri2d = { {0, 0}, {0, 0}, {0, 0} };
                            

                            if (hasTexture && idx0.size() > 1 && idx0[1] != -1 &&
                                idx1.size() > 1 && idx1[1] != -1 &&
                                idx2.size() > 1 && idx2[1] != -1) {
                                
                                int t0 = idx0[1] - 1;
                                int t1 = idx1[1] - 1;
                                int t2 = idx2[1] - 1;
                                
                                if (t0 >= 0 && t0 < static_cast<int>(texCoords.size()) &&
                                    t1 >= 0 && t1 < static_cast<int>(texCoords.size()) &&
                                    t2 >= 0 && t2 < static_cast<int>(texCoords.size())) {
                                    

                                    tri2d = {
                                        { texCoords[t0].m_u, texCoords[t0].m_v },
                                        { texCoords[t1].m_u, texCoords[t1].m_v },
                                        { texCoords[t2].m_u, texCoords[t2].m_v }
                                    };
                                }
                            }
                            
                            Polygon polygon(tri3d, tri2d);
                            polygon.sprite = sprite;
                            data.push_back(std::move(polygon));
                        }
                    }
                }
            }
        }
    }
    

    return true;
}

