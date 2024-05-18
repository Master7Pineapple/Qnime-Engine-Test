#include "libs.h"

    if (!CursorMode)
    {
        int somekey = GetCharPressed();
        if (somekey == 48) 
        {
            mode1 = modeArray[0];
            DisableCursor();
        }
        if (somekey == 49)
        {
            mode1 = modeArray[1];
            DisableCursor();
        }
        if (somekey == 50)
        {
            mode1 = modeArray[2];
            DisableCursor();
        }
        if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE) && mode1 != modeArray[3] && !RenderMode)
        {
            storedArrayMode = mode1;
            EnableCursor();
            SetMousePosition(int(GetRenderWidth()/2),int(GetRenderHeight()/2));
            mode1 = modeArray[3];
        }
        else if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE) && mode1 == modeArray[3])
        {
            vec1.clear();
            vec2.clear();
            mode1 = storedArrayMode;
            DisableCursor();
        }

        if (IsKeyPressed(KEY_RIGHT_CONTROL) && !RenderMode)
        {
            EnableCursor();
            SetMousePosition(int(GetRenderWidth()/2),int(GetRenderHeight()/2));
            RenderMode = true;
        }
        else if (IsKeyPressed(KEY_RIGHT_CONTROL) && RenderMode)
        {
            DisableCursor();
            RenderMode = false;
        }

        if (IsKeyPressed(KEY_RIGHT_SHIFT) && RenderMode && !FinalRenderMode)
        {
            FinalRenderMode = true;
        }
        else if (IsKeyPressed(KEY_RIGHT_SHIFT) && RenderMode && FinalRenderMode)
        {
            FinalRenderMode = false;
        }

        if (IsKeyDown(KEY_V))
        {   
            DimGridSwitchNumber += GetMouseWheelMove();
            if (DimGridSwitchNumber > 2)
            {           
                DimGridSwitchNumber = 0;
                DimGridMode = DimGridArray[0];
                
            }
            if (DimGridSwitchNumber < 0)
            {              
                DimGridSwitchNumber = 2;
                DimGridMode = DimGridArray[2];    
            }
            DimGridMode = DimGridArray[DimGridSwitchNumber];
        }

        if (IsKeyPressed(KEY_V))
        {
            CreateGrid = true;
        }

        if (IsKeyReleased(KEY_V))
        {
            CreateGrid = false;
        } 

        if (IsKeyDown(KEY_GRAVE))
        {
            CameraSpeed = 0.4f*(60.f/float(TargetFPS));
        }

        if (IsKeyDown(KEY_LEFT_SHIFT))
        {
            CameraSpeed = 0.025f*(60.f/float(TargetFPS));
        }

        if (IsKeyReleased(KEY_GRAVE) || IsKeyReleased(KEY_LEFT_SHIFT))
        {
            CameraSpeed = 0.1f*(60.f/float(TargetFPS));
        }

        if (IsKeyPressed(KEY_F11))
        {
            ToggleFullscreen();
        }
    }

    if (IsKeyPressed(KEY_E) && !NameMode && !EditNameMode && !RenderMode)
    {   
        CursorMode = true;
        EnableCursor();
        SetMousePosition(MX,MY);
        CursorSwitchNumber += 1;

        if (CursorSwitchNumber == 2)
        {   
            CursorSwitchNumber = 0;
            CursorMode = false;
            if (mode1 != modeArray[3])
            {
                DisableCursor();
            }
        }
    }

    if (IsWindowFullscreen())
    {
        SetWindowMaxSize(WindowWidth, WindowHeight);
        SetWindowSize(WindowWidth, WindowHeight);
        Point = {WindowWidth/2, WindowHeight/2};
    }
    if (!IsWindowFullscreen() && IsKeyPressed(KEY_F11))
    {
        SetWindowPosition(50,50);
        SetWindowSize(1300, 700);
    }

    // WARNING : WHEN CREATING ANOTHER FUNCTION THAT USES GetMouseWheelMove(), BE AWARE OF FUNCTIONS CONTROLS INTERVENE
    if (!CursorMode && !(GetMouseWheelMove() != 0 && IsKeyDown(KEY_V)) && !(CloseMode) && mode1 != modeArray[3] && !RenderMode)
    {
        UpdateCameraPro(&camera,
            (Vector3){
                (IsKeyDown(KEY_W) || IsKeyPressed(KEY_UP))*CameraSpeed -      // Move forward-backward
                (IsKeyDown(KEY_S) || IsKeyPressed(KEY_DOWN))*CameraSpeed,    
                (IsKeyDown(KEY_D) || IsKeyPressed(KEY_RIGHT))*CameraSpeed -      // Move right-left
                (IsKeyDown(KEY_A) || IsKeyPressed(KEY_LEFT))*CameraSpeed,
                (IsKeyDown(KEY_SPACE))*CameraSpeed -
                (IsKeyDown(KEY_Z)&&IsKeyUp(KEY_LEFT_CONTROL))*CameraSpeed        // Move up-down
            },
            (Vector3){
                GetMouseDelta().x*MouseSens,                            // Rotation: yaw
                GetMouseDelta().y*MouseSens,                            // Rotation: pitch
                0.0f                                               // Rotation: roll
            },
            GetMouseWheelMove()*-2.0f);

        wheel += GetMouseWheelMove();
        if (wheel > 5)
        {
            wheel = 5;
        }

        if (mode1 == modeArray[1] || mode1 == modeArray[2]) 
        {
            if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON) && VertexGroup.size() == 0)
            {
                StableETime = ETime;
                WarningMode = true;
            }
            if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON) && GroupSelect == -1)
            {
                StableETime = ETime;
                WarningMode = true;
            }
        }
        if (mode1 == modeArray[1])
        {
            if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON) && VertexGroup.size() > 0 && GroupSelect > -1)
            {
                if (MouseRayCollision.hit && GridSnap)
                {
                    vertices1.push_back(
                    {GridSpacing*(round((MouseRayCollision.point.x-remainder(StableGrid[0],GridSpacing))/GridSpacing))+remainder(StableGrid[0],GridSpacing),
                     GridSpacing*(round((MouseRayCollision.point.y-remainder(StableGrid[1],GridSpacing))/GridSpacing))+remainder(StableGrid[1],GridSpacing),
                     GridSpacing*(round((MouseRayCollision.point.z-remainder(StableGrid[2],GridSpacing))/GridSpacing))+remainder(StableGrid[2],GridSpacing),
                     float(GroupSelect),float(num1)});
                    num1 += 1; 
                }
                else if (MouseRayCollision.hit && !GridSnap)
                {
                    vertices1.push_back({MouseRayCollision.point.x,MouseRayCollision.point.y,MouseRayCollision.point.z,float(GroupSelect),float(num1)});
                    num1 += 1; 
                }
                else
                {
                    vertices1.push_back({camera.target.x,camera.target.y,camera.target.z,float(GroupSelect),float(num1)});
                    num1 += 1; 
                }
            }
        }
        if (mode1 == modeArray[2])
        {
            if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
            {
                StableETime2 = ETime;
            }
            if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON) && VertexGroup.size() > 0 && GroupSelect > -1)
            {
                if (ETime > StableETime2)
                {
                    if (MouseRayCollision.hit && !GridSnap)
                    {
                        vertices1.push_back({MouseRayCollision.point.x,MouseRayCollision.point.y,MouseRayCollision.point.z,float(GroupSelect),float(num1)});
                        num1 += 1; 
                    }
                    else if (!MouseRayCollision.hit)
                    {
                        vertices1.push_back({camera.target.x,camera.target.y,camera.target.z,float(GroupSelect),float(num1)});
                        num1 += 1; 
                    }
                    StableETime2 = ETime + float(DrawDelay)/10.f;
                }
            }     
        }
        /*
        if (vertices1.size() > 0)
        {     
            if (IsKeyDown(KEY_LEFT_CONTROL))
            {
                if(IsKeyPressed(KEY_Z))
                {
                    StableETime = ETime;
                    for (int i = 0; i < int(vertices1.size()); i++)
                    {
                        if (int(vertices1[i].v) == num1-1)
                        {
                            vertices1.erase(vertices1.begin()+i);
                            num1--;
                            CtrlZ = false;
                        }
                    }
                    if (CtrlZ)
                    {
                        for (int i = 0; i < int(lines1.size()); i++)
                        {
                            if (int(lines1[i].v) == num1-1)
                            {
                                lines1.erase(lines1.begin()+i);
                                num1--;
                            }
                        }
                    }
                }
                CtrlZ = true;
                if(IsKeyDown(KEY_Z) && ETime - StableETime > 0.3f)
                {
                    for (int i = 0; i < int(vertices1.size()); i++)
                    {
                        if (int(vertices1[i].v) == num1-1)
                        {
                            vertices1.erase(vertices1.begin()+i);
                            num1--;
                        }
                    }
                    if (CtrlZ)
                    {
                        for (int i = 0; i < int(lines1.size()); i++)
                        {
                            if (int(lines1[i].v) == num1-1)
                            {
                                lines1.erase(lines1.begin()+i);
                                num1--;
                            }
                        }
                    }
                    CtrlZ = true;
                }
            } 
        }
        */

        if (IsKeyPressed(KEY_P))
            {
                if (GridSnap)
                {
                    GridSnap = false;
                }
                else if (!GridSnap)
                {
                    GridSnap = true;
                }
            }

        if (CreateGrid)
        {
            if (IsKeyPressed(KEY_K) && NumOfGridLines > 0)
            {
                NumOfGridLines -= 1;
            }

            if (IsKeyPressed(KEY_L))
            {
                NumOfGridLines += 1;
            }

            if (IsKeyPressed(KEY_COMMA) && GridSpacing > 0.f)
            {
                GridSpacing -= 0.25f;
            }

            if (IsKeyPressed(KEY_PERIOD))
            {
                GridSpacing += 0.25f;
            }

            if (IsKeyPressed(KEY_LEFT_BRACKET) && Snap > 0.f)
            {
                Snap -= 0.25f;
            }

            if (IsKeyPressed(KEY_RIGHT_BRACKET))
            {
                Snap += 0.25f;
            }
        }
        if (mode1 == modeArray[2])
        {
            if (IsKeyPressed(KEY_COMMA) && DrawDelay > 1)
            {
                DrawDelay -= 1;
            }

            if (IsKeyPressed(KEY_PERIOD))
            {
                DrawDelay += 1;
            }
        }
    }
    #include "guicontrols.h"
    #include "guiresize.h"