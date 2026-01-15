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
class Camera;
class Renderer{
    public:
        Renderer(Window const& window, Settings const& settings);
        ~Renderer();
        void render(Scene const& scene);
        void projectMesh(Transform const& transform, Camera const& camera);
    private:
        std::vector<Polygon> m_collected;
        SDL_Renderer* m_Renderer;      
        Settings const& m_settings;
        Matrix4x4 m_projMatrix;
        void drawTriangle(Polygon const& t) const;
        Polygon projectPoligon(Transform const& transform, Polygon const& tri, Camera const& camera) const;
        Matrix4x4 getProjectionMatrix() const;
        
};

#endif