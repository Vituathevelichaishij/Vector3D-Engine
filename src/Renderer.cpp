#include "Renderer.h"

Renderer::Renderer(Window const& window, Settings const& settings):m_settings(settings){
        m_Renderer = SDL_CreateRenderer( window.gWindow,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        SDL_SetRenderDrawBlendMode(m_Renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(m_Renderer, 0x0, 0x0, 0x0, 0x0 );     
}
Renderer::~Renderer(){
    SDL_DestroyRenderer(m_Renderer);
    m_Renderer=NULL;
}


void Renderer::render(Scene const& scene){
    SDL_RenderClear(m_Renderer);
    SDL_SetRenderDrawColor(m_Renderer,255,0,0,255);

    for(auto& obj :scene.m_objects){
        renderMesh(obj.second.m_transform);
    }
    SDL_SetRenderDrawColor(m_Renderer,0,0,0,0);
    SDL_RenderPresent(m_Renderer);
}



void Renderer::renderMesh(Transform const& transform) const{
    for(auto const& tr : transform.m_mesh){
        Triangle tri=offsetPoligon(transform, tr);
        drawTriangle(tri);
    }
}


Triangle Renderer::offsetPoligon(Transform const& transform, Triangle const& tri) const{
    Vector3D a=tri.m_a;
    Vector3D b=tri.m_b;
    Vector3D c=tri.m_c;





    const Vector3D& angs=transform.m_rotation;
    float const f=M_PI/180;
    Matrix4x4 rotX = {{
        { 1,  0,                 0,                0 },
        { 0,  std::cosf(angs.m_x*f),  -std::sinf(angs.m_x*f),  0 },
        { 0,  std::sinf(angs.m_x*f),   std::cosf(angs.m_x*f),  0 },
        { 0,  0,                 0,                1 }
    }};
    a=vectorXmatrix4x4(a,rotX);
    b=vectorXmatrix4x4(b,rotX);
    c=vectorXmatrix4x4(c,rotX);


    Matrix4x4 rotY = {{
    {  std::cosf(angs.m_y*f), 0, std::sinf(angs.m_y*f), 0 },
    {  0,               1, 0,               0 },
    { -std::sinf(angs.m_y*f), 0, std::cosf(angs.m_y*f), 0 },
    {  0,               0, 0,               1 }
    }};

    a=vectorXmatrix4x4(a,rotY);
    b=vectorXmatrix4x4(b,rotY);
    c=vectorXmatrix4x4(c,rotY);

    Matrix4x4 rotZ = {{
    { std::cosf(angs.m_z*f), -std::sinf(angs.m_z*f), 0, 0 },
    { std::sinf(angs.m_z*f),  std::cosf(angs.m_z*f), 0, 0 },
    { 0,                0,               1, 0 },
    { 0,                0,               0, 1 }
    }};

    a=vectorXmatrix4x4(a,rotZ);
    b=vectorXmatrix4x4(b,rotZ);
    c=vectorXmatrix4x4(c,rotZ);

    a=a+transform.m_position;
    b=b+transform.m_position;
    c=c+transform.m_position;





    return Triangle(a,b,c);


}





void Renderer::drawTriangle(Triangle const& t) const{
    Matrix4x4 matrix=getProjectionMatrix();

    Vector3D a=vectorXmatrix4x4(t.m_a,matrix);
    Vector3D b=vectorXmatrix4x4(t.m_b,matrix);
    Vector3D c=vectorXmatrix4x4(t.m_c,matrix);
    
    int x1= (a.m_x+1)*m_settings.m_windowWidth/2;
    int y1= (a.m_y+1)*m_settings.m_windowHeight/2;

    int x2= (b.m_x+1)*m_settings.m_windowWidth/2;
    int y2= (b.m_y+1)*m_settings.m_windowHeight/2;

    int x3= (c.m_x+1)*m_settings.m_windowWidth/2;
    int y3= (c.m_y+1)*m_settings.m_windowHeight/2;


    
    

    SDL_RenderDrawLine(m_Renderer,x1,y1,x2,y2);
    SDL_RenderDrawLine(m_Renderer,x1,y1,x3,y3);
    SDL_RenderDrawLine(m_Renderer,x3,y3,x2,y2);
}






Matrix4x4 Renderer::getProjectionMatrix() const{
    float h=m_settings.m_windowHeight;
    float w=m_settings.m_windowWidth;

    float pov2=m_settings.m_pointOfViewAngle/2;

    float zfar=m_settings.m_maxDistance;
    float znear=m_settings.m_screenDistance;

    float tan= std::tan(3.14*pov2/180);

    
    Matrix4x4 restult={{{h/(w*tan),0,0,0},
                        {0,1/tan,0,0},
                        {0,0,zfar/(zfar-znear),1},
                        {0,0,-zfar*znear/(zfar-znear),0}}};

    return restult;
}