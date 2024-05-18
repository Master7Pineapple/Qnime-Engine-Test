#include "libs.h"
#include "variables.h" 
#include "functions.h"

int main()
{
    // INITIATE
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(WindowWidth, WindowHeight, "Engine");
    SetWindowMaxSize(WindowWidth, WindowHeight);
    //SetWindowPosition(100, 100);

    Camera camera = { 0 };
    camera.position = (Vector3){ 0.0f, 0.0f, 0.0f }; 
    camera.target = (Vector3){ 0.0f, 0.0f, -10.0f };     
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };       
    camera.fovy = 45.0f;                                
    camera.projection = CAMERA_PERSPECTIVE;
    ////////////////////////////////////////////////
    ////////////////////////////////////////////////
    Camera camera1 = { 0 };
    camera1.fovy = 45.0f;
    camera1.up.y = 1.0f;
    camera1.target = {0.f,0.f,0.01f};
    camera1.position = {0.f,10.f,0.f};

    RenderTexture screencamera1 = LoadRenderTexture(GetRenderWidth()/5, GetRenderHeight()/5);
    ////////////////////////////////////////////////
    Camera camera2 = { 0 };
    camera2.fovy = 45.0f;
    camera2.up.y = 1.0f;
    camera2.target = {0.f,0.f,0.01f};
    camera2.position = {0.f,10.f,0.f};

    RenderTexture screencamera2 = LoadRenderTexture(GetRenderWidth()/5, GetRenderHeight()/5);

    DisableCursor();           
    SetExitKey(NULL);
    int TargetFPS = GetMonitorRefreshRate(0);
    float CameraSpeed = 0.1f*(60.f/float(TargetFPS));
    SetTargetFPS(TargetFPS);
    ToggleFullscreen();

    // LOAD FILES
    Font lumberfont = LoadFontEx("resources/Lumberjack/Lumberjack.otf", 256, 0, 255); 
    Texture2D texture1 = LoadTexture("resources/Vertex.png");

    // UPDATE
    while (!WindowShouldClose())    
    {   
        int fps = GetFPS();
        Point = GetWorldToScreen({(camera.target.x),(camera.target.y),(camera.target.z)},camera); 
        
        //CONTROLS
        #include "controls.h"
        ClearBackground({35,35,35,255});
        ETime = GetTime();

        if (CreateGrid)
        {
            BeginTextureMode(screencamera1);
                ClearBackground({35,35,35,255});
                
                BeginMode3D(camera1);
                camera1.position = {camera.target.x,camera.target.y-12.f+float(5.f*(NumOfGridLines + GridSpacing)),camera.target.z};
                camera1.target = {camera.target.x,camera.target.y,camera.target.z+0.01f};
                    
                #include "draw3d2.h"
            
                EndMode3D();
                
            EndTextureMode();

            BeginTextureMode(screencamera2);
                ClearBackground({35,35,35,255});
                
                BeginMode3D(camera2);
                camera2.position = {camera.target.x-12.f+float(5.f*(NumOfGridLines + GridSpacing)),Snap*(round(camera.target.y/Snap)),Snap*(round(camera.target.z/Snap))};
                camera2.target = {camera.target.x,camera.target.y,camera.target.z};
                    
                #include "draw3d3.h"
            
                EndMode3D();
                
            EndTextureMode();
        }

        BeginDrawing();
            BeginMode3D(camera);
            
            #include "draw3d.h"
            
            if (lines1.size() > 0)
            {
                /*
                float offsetx = (vertices1[1].x + vertices1[0].x)/2;
                float offsety = (vertices1[1].y + vertices1[0].y)/2;
                float offsetz = (vertices1[1].z + vertices1[0].z)/2;
                */
                Vector3 vert = {((vertices1[1].x + vertices1[0].x)/2),
                ((vertices1[1].y + vertices1[0].y)/2),
                ((vertices1[1].z + vertices1[0].z)/2)};
                Vector3 vertmid = {(vertices1[1].x + vertices1[0].x)/2,
                (vertices1[1].y + vertices1[0].y)/2,
                (vertices1[1].z + vertices1[0].z)/2};

                vert = rotate_point(
                {vertices1[1].x,vertices1[1].y,vertices1[1].z},
                {vertices1[0].x,vertices1[0].y,vertices1[0].z},
                vert,ETime);

                Draw3DBillboard(camera,texture1,vert,0.1f,YELLOW);
                Draw3DBillboard(camera,texture1,vertmid,0.1f,YELLOW);
            }

            DrawLine3D({0,0,0},{0,1,0},YELLOW);
            DrawLine3D({0,0,0},{1,0,0},RED);
            DrawLine3D({0,0,0},{0,0,1},BLUE);
            
            EndMode3D();
            
            #include"draw2d.h"

            if (!(CursorMode || CloseMode))
            {
                DrawTextEx(lumberfont,".",{Point.x-3.f,Point.y-20.f},30.f,0.f,WHITE);
            }
            DrawTextEx(lumberfont, TextFormat("%d %c %d %d",fps,mode1,vertices1.size(),wheel), {10,10}, 50.0, 2.0, WHITE);
            
            if (CreateGrid)
            {
                DrawTextureRec(screencamera1.texture,{ 0.f, 0.f, (float)screencamera1.texture.width,
                 (float)-screencamera1.texture.height },
                 (Vector2){0.f, float(GetRenderHeight())/10}, WHITE);
                DrawTextureRec(screencamera2.texture,{ 0.f, 0.f, (float)screencamera2.texture.width,
                 (float)-screencamera2.texture.height },
                 (Vector2){0.f, float(GetRenderHeight())/10 + 216.f}, WHITE);
            }

            #include "render.h"

        EndDrawing();
    }
}
