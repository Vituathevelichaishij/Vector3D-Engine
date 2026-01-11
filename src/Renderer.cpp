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
        renderMesh(obj.second->m_transform, *scene.find<Camera>());
    }
    SDL_SetRenderDrawColor(m_Renderer,0,0,0,0);
    SDL_RenderPresent(m_Renderer);
}



void Renderer::renderMesh(Transform const& transform, Camera const& camera) const{
    std::vector<Triangle> sorted;
    for(auto const& tr : transform.m_mesh.data){
        sorted.push_back(offsetPoligon(transform, tr, camera));

    }
    sort(sorted.begin(),sorted.end(),[](Triangle const& a, Triangle const& b){return a.m_N.m_z<a.m_N.m_z;});
    for(auto const& tr: sorted){
        if(dotProduct(tr.m_N,tr.m_a-camera.m_transform.m_position)<0){
            drawTriangle(tr);
        }
    }



}


Triangle Renderer::offsetPoligon(Transform const& transform, Triangle const& tri, Camera const& camera) const{
    
    Vector3D a=tri.m_a - camera.m_transform.m_position;
    Vector3D b=tri.m_b - camera.m_transform.m_position;
    Vector3D c=tri.m_c - camera.m_transform.m_position;
    Vector3D N=tri.m_N;

    const Vector3D& angs=transform.m_rotation - camera.m_transform.m_rotation;

    a.rotate(angs.m_x,angs.m_y,angs.m_z);
    b.rotate(angs.m_x,angs.m_y,angs.m_z);
    c.rotate(angs.m_x,angs.m_y,angs.m_z);
    N.rotate(angs.m_x,angs.m_y,angs.m_z);
    
    a=vectorXvectorPart(a,transform.m_size);
    b=vectorXvectorPart(b,transform.m_size);
    c=vectorXvectorPart(c,transform.m_size);

    a=a+transform.m_position;
    b=b+transform.m_position;
    c=c+transform.m_position;

    return Triangle(a,b,c,N);


} 





void Renderer::drawTriangle(Triangle const& t) const{
    Matrix4x4 matrix=getProjectionMatrix();
    
    Vector3D a=vectorXmatrix4x4(t.m_a,matrix);
    Vector3D b=vectorXmatrix4x4(t.m_b,matrix);
    Vector3D c=vectorXmatrix4x4(t.m_c,matrix);
    
    float x1= (a.m_x+1)*m_settings.m_windowWidth/2;
    float y1= (a.m_y+1)*m_settings.m_windowHeight/2;

    float x2= (b.m_x+1)*m_settings.m_windowWidth/2;
    float y2= (b.m_y+1)*m_settings.m_windowHeight/2;

    float x3= (c.m_x+1)*m_settings.m_windowWidth/2;
    float y3= (c.m_y+1)*m_settings.m_windowHeight/2;
    FlatLum lum;

    const std::vector< SDL_Vertex > verts ={
        {SDL_FPoint{x1,y1}, SDL_Colour{255,0,0,255},SDL_FPoint{0}},
        {SDL_FPoint{x2,y2}, SDL_Colour{0,255,0,255},SDL_FPoint{0}},
        {SDL_FPoint{x3,y3}, SDL_Colour{0,0,255,255},SDL_FPoint{0}}
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