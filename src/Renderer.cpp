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

    auto cam=scene.findComponents<Camera>("Camera")[0];
    m_camMatrix=cam->getCameraMatrix();
    m_camPos=cam->owner->m_transform.m_position;

    m_lightSources=scene.findComponents<Light>("Light");


    for(auto& obj :scene.m_objects){
        
        projectMesh(obj.second->m_transform);
    }
    clipPolygons();


    
    sort(m_collected.begin(),m_collected.end(),[](Polygon const& a, Polygon const& b){
            float z1 = std::max({a.tri.m_a.m_z, a.tri.m_b.m_z, a.tri.m_c.m_z});
            float z2 = std::max({b.tri.m_a.m_z, b.tri.m_b.m_z, b.tri.m_c.m_z});
        return z1>z2;
    });


    for(auto const& tr: m_collected){
        
        drawTriangle(tr);

    }


    m_collected.clear();



    SDL_SetRenderDrawColor(m_Renderer,0,0,0,0);
    SDL_RenderPresent(m_Renderer);
}



void Renderer::projectMesh(Transform& transform){
    for(auto& tr : transform.m_mesh.data){
        
        projectPoligon(transform, tr);

    }


}

void Renderer::calculateLight(Polygon& pol){
    pol.m_lum=m_lightSources[0]->getLuminocity(pol.tri);
    
}

void Renderer::clipPolygons(){
    std::vector<Polygon> result;
    Vector3D plains[][2]={{{0,0,0.1},{0,0, 1}}};
    for(auto &pol :m_collected){
        polygonClipAgainstPlane(plains[0][0], plains[0][1],pol,result);
    }
    m_collected=std::move(result);
}

void Renderer::projectPoligon(Transform const& transform, Polygon const& tri){
    
    


    Matrix4x4 worldMatrix=getRotMatrix(transform.m_rotation)*getTransMatrix(transform.m_position);


    Vector3D a=vectorXmatrix4x4(tri.tri.m_a,worldMatrix);
    Vector3D b=vectorXmatrix4x4(tri.tri.m_b,worldMatrix);
    Vector3D c=vectorXmatrix4x4(tri.tri.m_c,worldMatrix);

    Polygon result(Triangle{a,b,c});
    

    if(dotProduct(result.tri.m_N,a-m_camPos)>0) return;

    
    calculateLight(result);



    result.tri.m_a=vectorXmatrix4x4(result.tri.m_a,m_camMatrix);
    result.tri.m_b=vectorXmatrix4x4(result.tri.m_b,m_camMatrix);
    result.tri.m_c=vectorXmatrix4x4(result.tri.m_c,m_camMatrix);

    m_collected.emplace_back(std::move(result));
    





} 





void Renderer::drawTriangle(Polygon const& t) const{
    
    
    Vector3D a=vectorXmatrix4x4(t.tri.m_a,m_projMatrix);
    Vector3D b=vectorXmatrix4x4(t.tri.m_b,m_projMatrix);
    Vector3D c=vectorXmatrix4x4(t.tri.m_c,m_projMatrix);
    
    float x1= (a.m_x+1)*m_settings.m_windowWidth/2;
    float y1= (1-a.m_y)*m_settings.m_windowHeight/2;

    float x2= (b.m_x+1)*m_settings.m_windowWidth/2;
    float y2= (1-b.m_y)*m_settings.m_windowHeight/2;

    float x3= (c.m_x+1)*m_settings.m_windowWidth/2;
    float y3= (1-c.m_y)*m_settings.m_windowHeight/2;
    float m=t.m_lum;
   

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
















void Renderer::polygonClipAgainstPlane(Vector3D& plane_p, Vector3D plane_n, Polygon& in, std::vector<Polygon>& result){

	plane_n.normalize();


	auto dist = [&](Vector3D const &p){
		return (dotProduct(plane_n,p) - dotProduct(plane_n, plane_p));
	};


		Vector3D* inside_points[3];  int nInsidePointCount = 0;
		Vector3D* outside_points[3]; int nOutsidePointCount = 0;


		float d0 = dist(in.tri.m_a);
		float d1 = dist(in.tri.m_b);
		float d2 = dist(in.tri.m_c);

	if (d0 >= 0) { inside_points[nInsidePointCount++] = &in.tri.m_a; }
	else { outside_points[nOutsidePointCount++] = &in.tri.m_a; }
	if (d1 >= 0) { inside_points[nInsidePointCount++] = &in.tri.m_b; }
    else { outside_points[nOutsidePointCount++] = &in.tri.m_b; }
	if (d2 >= 0) { inside_points[nInsidePointCount++] = &in.tri.m_c; }
	else { outside_points[nOutsidePointCount++] = &in.tri.m_c; }


	if (nInsidePointCount == 0){


		return; 
	}

	if (nInsidePointCount == 3){

		result.push_back(std::move(in));

		return; 
	}

	if (nInsidePointCount == 1 && nOutsidePointCount == 2){

        Polygon out = in;

		out.tri.m_a = *inside_points[0];

		out.tri.m_b = vectorXplainIntersec(plane_p, plane_n, *inside_points[0], *outside_points[0]);
		out.tri.m_c = vectorXplainIntersec(plane_p, plane_n, *inside_points[0], *outside_points[1]);

        result.push_back(out);

		return; 
	}

	if (nInsidePointCount == 2 && nOutsidePointCount == 1){

        Polygon out1=in;

        Polygon out2=in;
        
		out1.tri.m_a = *inside_points[0];
		out1.tri.m_b = *inside_points[1];
		out1.tri.m_c = vectorXplainIntersec(plane_p, plane_n, *inside_points[0], *outside_points[0]);

		out2.tri.m_a = *inside_points[1];
		out2.tri.m_b = out1.tri.m_c;
		out2.tri.m_c = vectorXplainIntersec(plane_p, plane_n, *inside_points[1], *outside_points[0]);
        

        result.push_back(out1);
        result.push_back(out2);
		return; 
	}
}


