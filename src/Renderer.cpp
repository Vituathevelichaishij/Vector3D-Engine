#include "Renderer.h"
#include "Camera.h"
#include "Light.h"
Renderer::Renderer(Window const& window, Settings const& settings):m_settings(settings){
        m_Renderer = SDL_CreateRenderer( window.gWindow,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        m_projMatrix=getProjectionMatrix();



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
        renderMesh(obj.second->m_transform,  *dynamic_cast<Camera*>(scene.findComponents("Camera")[0]));
    }

    sort(m_collected.begin(),m_collected.end(),[](Triangle const& a, Triangle const& b){
        float z1=a.m_a.m_z+a.m_b.m_z+a.m_c.m_z;
        float z2=b.m_a.m_z+b.m_b.m_z+b.m_c.m_z;
        return z1>z2;
    });


    for(auto const& tr: m_collected){
        
        drawTriangle(tr,scene);

    }


    m_collected.clear();



    SDL_SetRenderDrawColor(m_Renderer,0,0,0,0);
    SDL_RenderPresent(m_Renderer);
}



void Renderer::renderMesh(Transform const& transform, Camera const& camera){
    for(auto const& tr : transform.m_mesh.data){
        Triangle tri=offsetPoligon(transform, tr, camera);
        if(dotProduct(tri.m_N,tri.m_a-camera.m_position)<0){
            m_collected.push_back(tri);
        }

    }


}

Triangle Renderer::offsetPoligon(Transform const& transform, Triangle const& tri, Camera const& camera) const{
    
    Vector3D a=tri.m_a;
    Vector3D b=tri.m_b;
    Vector3D c=tri.m_c;

    const Vector3D& angs=transform.m_rotation;

    Matrix4x4 worlMatrix=getRotMatrix(angs)*getTransMatrix(transform.m_position);


    a=vectorXmatrix4x4(a,worlMatrix);
    b=vectorXmatrix4x4(b,worlMatrix);
    c=vectorXmatrix4x4(c,worlMatrix);
    


    return Triangle(a,b,c);


} 





void Renderer::drawTriangle(Triangle const& t , const Scene& s) const{
    
    
    Vector3D a=vectorXmatrix4x4(t.m_a,m_projMatrix);
    Vector3D b=vectorXmatrix4x4(t.m_b,m_projMatrix);
    Vector3D c=vectorXmatrix4x4(t.m_c,m_projMatrix);
    
    float x1= (a.m_x+1)*m_settings.m_windowWidth/2;
    float y1= (1-a.m_y)*m_settings.m_windowHeight/2;

    float x2= (b.m_x+1)*m_settings.m_windowWidth/2;
    float y2= (1-b.m_y)*m_settings.m_windowHeight/2;

    float x3= (c.m_x+1)*m_settings.m_windowWidth/2;
    float y3= (1-c.m_y)*m_settings.m_windowHeight/2;
    float m=dynamic_cast<Light*>(s.findComponents("Light")[0])->getLuminocity(t);
    
    const std::vector< SDL_Vertex > verts ={
        {SDL_FPoint{x1,y1}, SDL_Colour{255*m,255*m,255*m,255},SDL_FPoint{0}},
        {SDL_FPoint{x2,y2}, SDL_Colour{255*m,255*m,255*m,255},SDL_FPoint{0}},
        {SDL_FPoint{x3,y3}, SDL_Colour{255*m,255*m,255*m,255},SDL_FPoint{0}}
    };
    SDL_RenderGeometry(m_Renderer,NULL,verts.data(),verts.size(),nullptr,0);

    /*  
    SDL_RenderDrawLine(m_Renderer,x1,y1,x2,y2);
    SDL_RenderDrawLine(m_Renderer,x1,y1,x3,y3);
    SDL_RenderDrawLine(m_Renderer,x3,y3,x2,y2);
    */
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