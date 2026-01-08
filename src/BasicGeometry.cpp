#include "BasicGeometry.h"
Vector3D::Vector3D(float x, float y, float z): m_x(x),m_y(y), m_z(z){}

Vector3D Vector3D::operator+(const Vector3D &n)const{
    return Vector3D(m_x+n.m_x,m_y+n.m_y,m_z+n.m_z);
}
Vector3D Vector3D::operator-(const Vector3D &n)const{
    return Vector3D(m_x-n.m_x,m_y-n.m_y,m_z-n.m_z);
}
Vector3D Vector3D::operator-(float &n){
    return Vector3D(m_x-n,m_y-n,m_z-n);
}



Vector3D Vector3D::operator*(float n){
    return Vector3D(m_x*n,m_y*n,m_z*n);
}
Vector3D Vector3D::operator/(float n){
    return Vector3D(m_x/n,m_y/n,m_z/n);
}


void Vector3D::normalize(){
    float length=std::sqrt(m_x*m_x+m_y*m_y+m_z*m_z);
    m_x/=length;
    m_y/=length;
    m_z/=length;
}

Triangle::Triangle(Vector3D const& a, Vector3D const& b, Vector3D const& c){
    m_a=a;
    m_b=b;
    m_c=c;
    Vector3D first={b.m_x-a.m_x,b.m_y-a.m_y,b.m_z-a.m_z};

    Vector3D second={c.m_x-a.m_x,c.m_y-a.m_y,c.m_z-a.m_z};

    m_N={first.m_y*second.m_z-first.m_z*second.m_y,
        first.m_z*second.m_x-first.m_x*second.m_z,
        first.m_x*second.m_y-first.m_y*second.m_x,
    };
}



Vector3D vectorXmatrix4x4(Vector3D const& v, Matrix4x4 const& m){
    Vector3D result;
    

    result.m_x = v.m_x * m.data[0][0] +
              v.m_y * m.data[1][0] +
              v.m_z * m.data[2][0] +
              v.m_w  * m.data[3][0];

    result.m_y = v.m_x * m.data[0][1] +
              v.m_y * m.data[1][1] +
              v.m_z * m.data[2][1] +
              v.m_w  * m.data[3][1];

    result.m_z = v.m_x * m.data[0][2] +
              v.m_y * m.data[1][2] +
              v.m_z * m.data[2][2] +
              v.m_w  * m.data[3][2];

    result.m_w = v.m_x * m.data[0][3] +
              v.m_y * m.data[1][3] +
              v.m_z * m.data[2][3] +
              v.m_w  * m.data[3][3];
    if(result.m_w!=0){
        result.m_x/=result.m_w;
        result.m_y/=result.m_w;
        result.m_z/=result.m_w;
    }
    

    return result;



}