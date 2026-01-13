#include "Camera3D.h"
#include "GameObject.h"
#include "ComponentFactory.h"
void register_Camera3D()
{ComponentFactory::init().registerComponent("Camera3D", []() {return std::make_unique<Camera3D>();   });}

void Camera3D::update(Uint32 dT){
    m_angles=owner->m_transform.m_rotation;
    m_position=owner->m_transform.m_position;
}
Matrix4x4 Camera3D::getCameraMatrix(){
    Matrix4x4 result;
    result=getTransMatrix(m_position);
    return result;
}

void  Camera3D::init(YAML::Node const& data){}
void Camera3D::start(){}