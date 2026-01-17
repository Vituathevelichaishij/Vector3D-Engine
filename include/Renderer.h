#ifndef RENDERER_H
#define RENDERER_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cmath>
#include "Settings.h"
#include "Window.h"
#include "BasicGeometry.h"
#include "Transform.h"
#include "Scene.h"
class Light;
class Camera;
class Renderer{
    public:
        Renderer(Window const& window, Settings const& settings);
        ~Renderer();
        void render(Scene const& scsene);
        void projectMesh(Transform& transform);
    private:
        std::vector<Polygon> m_collected;
        std::vector<Light*> m_lightSources;
        SDL_Renderer* m_Renderer;      
        Settings const& m_settings;
        Matrix4x4 m_projMatrix;
        Matrix4x4 m_camMatrix;
        Vector3D m_camPos;
        void drawTriangle(Polygon const& t) const;
        void projectPoligon(Transform const& transform, Polygon const& tri);
        Matrix4x4 getProjectionMatrix() const;
        void calculateLight(Polygon& pol);
        void polygonClipAgainstPlane(Vector3D& plane_p, Vector3D plane_n, Polygon& in, std::vector<Polygon>& result);
        // void polygonClipAgainstPlane(Vector3D const& plane_p,Vector3D plane_n,Polygon const& in, std::vector<Polygon>& result);
        void clipPolygons();



        
};

#endif