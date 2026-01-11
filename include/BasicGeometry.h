#ifndef VECTOR_H
#define VECTOR_H
#include <vector>
#include <cmath>
#include <iostream>

#ifndef M_PI 
#define M_PI    3.14159265358979323846264338327950288
#endif

class Vector3D{
    public:
        float m_x=0;
        float m_y=0;
        float m_z=0;
        float m_w=1;
        Vector3D(float x, float y, float z);
        Vector3D()=default;
        Vector3D operator+(const Vector3D &n) const;
        Vector3D operator-(const Vector3D &n) const;
        Vector3D operator-(float &n);
        Vector3D operator*(float n);
        Vector3D operator/(float n);
        void normalize();
        void rotate(float dX, float dY, float dZ);
        float length() const;


};

class Triangle{
    public:
        Triangle(Vector3D const& a, Vector3D const& b, Vector3D const& c);
        Triangle(Vector3D const& a, Vector3D const& b,Vector3D const& c, Vector3D const& N);
        Vector3D m_a;
        Vector3D m_b;
        Vector3D m_c;
        Vector3D m_N;
    private:
};


Vector3D vectorXvectorPart(Vector3D const& a, Vector3D const& b);

struct Matrix4x4{
    float data[4][4];
};
Vector3D vectorXmatrix4x4(Vector3D const& v, Matrix4x4 const& m);

Matrix4x4 matrixXmatrix4x4(Matrix4x4 const& a, Matrix4x4 const& b);

float dotProduct(Vector3D const& a, Vector3D const& b);

#endif