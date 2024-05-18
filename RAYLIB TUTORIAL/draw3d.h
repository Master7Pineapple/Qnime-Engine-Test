#include "libs.h"

    MouseRay = GetMouseRay(GetWorldToScreen({camera.target.x,camera.target.y,camera.target.z},camera),camera);
    DrawGrid(20, 1.0f);
    if (sizeof(StableGrid) / sizeof(float) > 0)
    {
        if (StableGrid[5] == 0.f)
        {
            MouseRayCollision = GetRayCollisionQuad(MouseRay, 
            {StableGrid[0]-((StableGrid[4]-1)*StableGrid[3]),StableGrid[1],StableGrid[2]-((StableGrid[4]-1)*StableGrid[3])},
            {StableGrid[0]+((StableGrid[4]-1)*StableGrid[3]),StableGrid[1],StableGrid[2]-((StableGrid[4]-1)*StableGrid[3])},
            {StableGrid[0]+((StableGrid[4]-1)*StableGrid[3]),StableGrid[1],StableGrid[2]+((StableGrid[4]-1)*StableGrid[3])},
            {StableGrid[0]-((StableGrid[4]-1)*StableGrid[3]),StableGrid[1],StableGrid[2]+((StableGrid[4]-1)*StableGrid[3])});
        }
        else if (StableGrid[5] == 1.f)
        {
            MouseRayCollision = GetRayCollisionQuad(MouseRay, 
            {StableGrid[0]-((StableGrid[4]-1)*StableGrid[3]),StableGrid[1]-((StableGrid[4]-1)*StableGrid[3]),StableGrid[2]},
            {StableGrid[0]+((StableGrid[4]-1)*StableGrid[3]),StableGrid[1]-((StableGrid[4]-1)*StableGrid[3]),StableGrid[2]},
            {StableGrid[0]+((StableGrid[4]-1)*StableGrid[3]),StableGrid[1]+((StableGrid[4]-1)*StableGrid[3]),StableGrid[2]},
            {StableGrid[0]-((StableGrid[4]-1)*StableGrid[3]),StableGrid[1]+((StableGrid[4]-1)*StableGrid[3]),StableGrid[2]});
        }
        else if (StableGrid[5] == 2.f)
        {
            MouseRayCollision = GetRayCollisionQuad(MouseRay, 
            {StableGrid[0],StableGrid[1]-((StableGrid[4]-1)*StableGrid[3]),StableGrid[2]-((StableGrid[4]-1)*StableGrid[3])},
            {StableGrid[0],StableGrid[1]+((StableGrid[4]-1)*StableGrid[3]),StableGrid[2]-((StableGrid[4]-1)*StableGrid[3])},
            {StableGrid[0],StableGrid[1]+((StableGrid[4]-1)*StableGrid[3]),StableGrid[2]+((StableGrid[4]-1)*StableGrid[3])},
            {StableGrid[0],StableGrid[1]-((StableGrid[4]-1)*StableGrid[3]),StableGrid[2]+((StableGrid[4]-1)*StableGrid[3])});
        }

        // MouseRayCollision2
        
        if (mode1 == modeArray[0] && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            for (int i = 0; i < int(vertices1.size()); i++)
            {
                VertexBox = {{vertices1[i].x-0.05f,vertices1[i].y-0.05f,vertices1[i].z-0.05f},
                 {vertices1[i].x+0.05f,vertices1[i].y+0.05f,vertices1[i].z+0.05f}};
                MouseRayCollision2 = GetRayCollisionBox(MouseRay,VertexBox);
                if (MouseRayCollision2.hit)
                {
                    SelectedVec = int(vertices1[i].v);
                    VertexBoxIsEmpty = false;
                    break;
                }
            }
            if (!MouseRayCollision2.hit)
            {
                VertexBoxIsEmpty = true;
                VertexBox = {};
                SelectedVec = -1;
            }
        }
        for (int i = 0; i < int(vertices1.size()); i++)
        {
            if (SelectedVec == int(vertices1[i].v) && SelectedVec > -1)
            {
                if (VertexSelect.size() == 0)
                {
                    DrawBoundingBox((BoundingBox){{vertices1[i].x-0.05f,vertices1[i].y-0.05f,vertices1[i].z-0.05f},
                    {vertices1[i].x+0.05f,vertices1[i].y+0.05f,vertices1[i].z+0.05f}},GRAY);
                }
                if (VertexSelect.size() == 1)
                {
                    DrawBoundingBox((BoundingBox){{vertices1[i].x-0.05f,vertices1[i].y-0.05f,vertices1[i].z-0.05f},
                    {vertices1[i].x+0.05f,vertices1[i].y+0.05f,vertices1[i].z+0.05f}},RED);
                }
            }
        }
        if (IsKeyPressed(KEY_O))
        {
            VertexSelect.clear();
        }
        if (mode1 == modeArray[0] && IsMouseButtonDown(MOUSE_RIGHT_BUTTON) && !VertexBoxIsEmpty && bool1)
        {
            if (VertexSelect.size() == 2)
            {     
                lines1.push_back({float(VertexSelect[0]),float(VertexSelect[1]),GroupSelect,numline1,0});
                numline1++;
                VertexSelect[0] = VertexSelect[1];
                VertexSelect.pop_back();
                bool1 = false;      
            }
            else if (VertexSelect.size() == 1)
            {
                if (SelectedVec != VertexSelect[0] && SelectedVec > -1)
                {
                    VertexSelect.push_back(SelectedVec);
                }
            }
            else if (VertexSelect.size() == 0 && SelectedVec > -1)
            {
                VertexSelect.push_back(SelectedVec);
            }
        }
        bool1 = true;
        
        if (MouseRayCollision.hit)
        {
            DrawDimGrid({StableGrid[0],StableGrid[1],StableGrid[2]},
             StableGrid[3],StableGrid[4],RED,DimGridArray[int(StableGrid[5])]);
        }
        else
        {
            DrawDimGrid({StableGrid[0],StableGrid[1],StableGrid[2]},
             StableGrid[3],StableGrid[4],GRAY,DimGridArray[int(StableGrid[5])]);
        }
    }
    if (CreateGrid)
    {
        DrawDimGrid({Snap*(round(camera.target.x/Snap)),Snap*(round(camera.target.y/Snap)),Snap*(round(camera.target.z/Snap))},
         GridSpacing,NumOfGridLines,RED,DimGridMode);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            StableGrid[0] = Snap*(round(camera.target.x/Snap));
            StableGrid[1] = Snap*(round(camera.target.y/Snap));
            StableGrid[2] = Snap*(round(camera.target.z/Snap));
            StableGrid[3] = float(GridSpacing);
            StableGrid[4] = float(NumOfGridLines);
            StableGrid[5] = float(DimGridSwitchNumber);
        }
    } 
    if (MouseRayCollision.hit && GridSnap)
    {
        Draw3DBillboard(camera,texture1,
        {GridSpacing*(round((MouseRayCollision.point.x-remainder(StableGrid[0],GridSpacing))/GridSpacing))+remainder(StableGrid[0],GridSpacing),
         GridSpacing*(round((MouseRayCollision.point.y-remainder(StableGrid[1],GridSpacing))/GridSpacing))+remainder(StableGrid[1],GridSpacing),
         GridSpacing*(round((MouseRayCollision.point.z-remainder(StableGrid[2],GridSpacing))/GridSpacing))+remainder(StableGrid[2],GridSpacing)},
         0.1f,GRAY);
    }

    if (MouseRayCollision.hit && !GridSnap)
    {
        Draw3DBillboard(camera,texture1,{MouseRayCollision.point.x,MouseRayCollision.point.y,MouseRayCollision.point.z},0.1f,GRAY);
    }

    for (int i = 0; i < int(vertices1.size()); i++)
    {   
        if (GroupSelect > -1)
        {
            if (int(vertices1[i].w) != GroupSelect)
            {
                Draw3DBillboard(camera,texture1,{vertices1.at(i).x,vertices1.at(i).y,vertices1.at(i).z},0.1f,DARKGRAY);
            }
            if (int(vertices1[i].w) == GroupSelect)
            {
                if (vec2.size() > 0)
                {
                    for (int j = 0; j < int(vec2.size()); j++)
                    {
                        if (int(vertices1[i].v) == vec2[j])
                        {
                            Draw3DBillboard(camera,texture1,{vertices1.at(i).x,vertices1.at(i).y,vertices1.at(i).z},0.1f,{255,255,255,255});
                            boollol = false;
                        }
                    }
                    if (boollol)
                    {
                        Draw3DBillboard(camera,texture1,{vertices1.at(i).x,vertices1.at(i).y,vertices1.at(i).z},0.1f,RED);
                    }
                    boollol = true;
                }
                else
                {
                    Draw3DBillboard(camera,texture1,{vertices1.at(i).x,vertices1.at(i).y,vertices1.at(i).z},0.1f,RED);
                }
            }
        }
        if (GroupSelect == -1)
        {
            Draw3DBillboard(camera,texture1,{vertices1.at(i).x,vertices1.at(i).y,vertices1.at(i).z},0.1f,DARKGRAY);
        }
    }

    for (int i = 0; i < int(lines1.size()); i++)
    {
        if (GroupSelect > -1)
        {
            if (int(lines1[i].z) != GroupSelect)
            {
                for (int i2 = 0; i2 < int(vertices1.size()); i2++)
                {
                    if (int(lines1[i].x) == int(vertices1[i2].v))
                    {
                        xval = i2;
                    }
                    if (int(lines1[i].y) == int(vertices1[i2].v))
                    {
                        yval = i2;
                    }
                    if (xval > -1 && yval > -1)
                    {
                        DrawLine3D({vertices1[xval].x,vertices1[xval].y,vertices1[xval].z},
                        {vertices1[yval].x,vertices1[yval].y,vertices1[yval].z},DARKGRAY);
                        xval = -1;
                        yval = -1;
                        break;
                    }
                }
            }
            if (int(lines1[i].z) == GroupSelect)
            {
                for (int i2 = 0; i2 < int(vertices1.size()); i2++)
                {
                    if (int(lines1[i].x) == int(vertices1[i2].v))
                    {
                        xval = i2;
                    }
                    if (int(lines1[i].y) == int(vertices1[i2].v))
                    {
                        yval = i2;
                    }
                    if (xval > -1 && yval > -1)
                    {
                        DrawLine3D({vertices1[xval].x,vertices1[xval].y,vertices1[xval].z},
                        {vertices1[yval].x,vertices1[yval].y,vertices1[yval].z},RED);
                        xval = -1;
                        yval = -1;
                        break;
                    }
                }
            }
        }
        if (GroupSelect == -1)
        {
            for (int i2 = 0; i2 < int(vertices1.size()); i2++)
            {
                if (int(lines1[i].x) == int(vertices1[i2].v))
                {
                    xval = i2;
                }
                if (int(lines1[i].y) == int(vertices1[i2].v))
                {
                    yval = i2;
                }
                if (xval > -1 && yval > -1)
                {
                    DrawLine3D({vertices1[xval].x,vertices1[xval].y,vertices1[xval].z},
                    {vertices1[yval].x,vertices1[yval].y,vertices1[yval].z},DARKGRAY);
                    xval = -1;
                    yval = -1;
                    break;
                }
            }
        }    
    }