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
class Renderer{
    public:
        Renderer(Window const& window, Settings const& settings);
        ~Renderer();
        void render(Scene const& scene);
        void renderMesh(Transform const& transform) const;
    private:
        SDL_Renderer* m_Renderer;       ///< SDL renderer used for drawing.
        Settings const& m_settings;
        void drawTriangle(Triangle const& t) const;
        Triangle offsetPoligon(Transform const& transform, Triangle const& tri) const;
        Matrix4x4 getProjectionMatrix() const;
};

#endif