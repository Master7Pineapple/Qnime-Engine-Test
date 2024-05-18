#include "libs.h"

    if (CreateGrid)
    {
        DrawTextEx(lumberfont,TextFormat("%s %d","K/L : Number of Slices = ",NumOfGridLines),
         {float((GetRenderWidth()/2)-180),float(GetRenderHeight()-216)},50.0,1.0,WHITE);
        DrawTextEx(lumberfont,TextFormat("%s %.2f","</> : Spacing = ",GridSpacing),
         {float((GetRenderWidth()/2)-180),float(GetRenderHeight()-256)},50.0,1.0,WHITE);
        DrawTextEx(lumberfont,TextFormat("%s %.2f","[/] : Snap = ",Snap),
         {float((GetRenderWidth()/2)-180),float(GetRenderHeight()-296)},50.0,1.0,WHITE);
    }

    if (mode1 == modeArray[2])
    {
        DrawTextEx(lumberfont,TextFormat("%s %.2f","</> : Draw Delay = ",float(DrawDelay)/10.f),
         {float((GetRenderWidth()/2)-180),float(GetRenderHeight()-176)},50.0,1.0,WHITE);
    }

    if (WarningMode && ETime - StableETime < 3.f)
    {
        if (VertexGroup.size() == 0)
        {
            DrawTextEx(lumberfont,TextFormat("%s","Add New Group to Draw Vertices"),
            {float((GetRenderWidth()-720)/2),float(GetRenderHeight())/5.4f},70.f,1.0,WHITE);
        }
        if (GroupSelect == -1)
        {
            DrawTextEx(lumberfont,TextFormat("%s","Select a Group to Draw Vertices"),
            {float((GetRenderWidth()-720)/2),(float(GetRenderHeight())/5.4f)-70.f},70.f,1.0,WHITE);
        }
    }

    #include "editvert.h"

    if (CursorMode && !(CloseMode))
    {     
        DrawRectangle((int)UIWindowRect1.at(0).x,(int)UIWindowRect1.at(0).y, 
         (int)UIWindowRect1.at(0).z,(int)UIWindowRect1.at(0).w,
         {(unsigned char)UIWindowColor1.at(0).x,(unsigned char)UIWindowColor1.at(0).y,
         (unsigned char)UIWindowColor1.at(0).z,(unsigned char)UIWindowColor1.at(0).w});

        if (VertexGroup.size() > 0 && (GroupSelect - slide) < 17 && (GroupSelect - slide) > -1) 
        {
         DrawRectangle((int)UIWindowBeRect1.at(4).x,(int)UIWindowBeRect1.at(4).y+((GroupSelect-slide)*40), 
         (int)UIWindowBeRect1.at(4).z,(int)UIWindowBeRect1.at(4).w,
         {(unsigned char)UIWindowBeColor1.at(4).x,(unsigned char)UIWindowBeColor1.at(4).y,
         (unsigned char)UIWindowBeColor1.at(4).z,(unsigned char)(UIWindowBeColor1.at(4).w)});
        }

        if (num3 >= 0)
        {
            DrawRectangle((int)UIWindowBeRect1.at(4).x,(int)UIWindowBeRect1.at(4).y+((num3-slide)*40), 
            (int)UIWindowBeRect1.at(4).z,(int)UIWindowBeRect1.at(4).w,
            {(unsigned char)UIWindowBeColor1.at(4).x,(unsigned char)UIWindowBeColor1.at(4).y,
            (unsigned char)UIWindowBeColor1.at(4).z,(unsigned char)UIWindowBeColor1.at(4).w});

            DrawRectangle((int)UIWindowBeRect1.at(2).x,(int)UIWindowBeRect1.at(2).y+((num3-slide)*40), 
            (int)UIWindowBeRect1.at(2).z,(int)UIWindowBeRect1.at(2).w,
            {(unsigned char)UIWindowBeColor1.at(2).x,(unsigned char)UIWindowBeColor1.at(2).y,
            (unsigned char)UIWindowBeColor1.at(2).z,(unsigned char)UIWindowBeColor1.at(2).w});

            DrawRectangle((int)UIWindowBeRect1.at(3).x,(int)UIWindowBeRect1.at(3).y+((num3-slide)*40), 
            (int)UIWindowBeRect1.at(3).z,(int)UIWindowBeRect1.at(3).w,
            {(unsigned char)UIWindowBeColor1.at(3).x,(unsigned char)UIWindowBeColor1.at(3).y,
            (unsigned char)UIWindowBeColor1.at(3).z,(unsigned char)UIWindowBeColor1.at(3).w});
        }

        DrawRectangle((int)UIWindowBeRect1.at(0).x,(int)UIWindowBeRect1.at(0).y, 
         (int)UIWindowBeRect1.at(0).z,(int)UIWindowBeRect1.at(0).w,
         {(unsigned char)UIWindowBeColor1.at(0).x,(unsigned char)UIWindowBeColor1.at(0).y,
         (unsigned char)UIWindowBeColor1.at(0).z,(unsigned char)UIWindowBeColor1.at(0).w});

        if (VertexGroup.size() > 16)
        {
            DrawRectangle((int)UIWindowBeRect1.at(1).x,(int)UIWindowBeRect1.at(1).y, 
             (int)UIWindowBeRect1.at(1).z,(int)UIWindowBeRect1.at(1).w,
             {(unsigned char)UIWindowBeColor1.at(1).x,(unsigned char)UIWindowBeColor1.at(1).y,
             (unsigned char)UIWindowBeColor1.at(1).z,(unsigned char)UIWindowBeColor1.at(1).w});
        }

        if (VertexGroup.size() > 0)
        {
            for (unsigned i = slide;i < VertexGroup.size();i++)
            {
                DrawTextEx(lumberfont,TextFormat("%s",VertexGroup[i].c_str()),
                {UIWindowRect1.at(0).x+80.f,UIWindowRect1.at(0).y+60.f+(float(i)*40.f-(slide*40.f))},50.0,1.0,WHITE);
            }
        }
        
        if (NameMode)
        {
            DrawRectangle(int((GetRenderWidth()-350)/2),int((GetRenderHeight()-150)/2),350,150,{50,50,50,255});
            DrawTextEx(lumberfont,TextFormat("%s","Enter Name :"),
             {float((GetRenderWidth()-210)/2),float((GetRenderHeight()-110)/2)},50.0,1.0,WHITE);
            for (unsigned int i = 0; i < GroupName.size(); i++)
            {
                DrawTextEx(lumberfont,TextFormat("%c",GroupName[i]),
                {float((GetRenderWidth()-290)/2)+float(i*30),float((GetRenderHeight()-10)/2)},50.0,1.0,WHITE);
            }
            if (IsKeyPressed(KEY_ESCAPE))
            {
                ExitNum -= 1;
                NameMode = false;
            }   
        }

        if (EditNameMode)
        {
            DrawRectangle(int((GetRenderWidth()-350)/2),int((GetRenderHeight()-150)/2),350,150,{50,50,50,255});
            DrawTextEx(lumberfont,TextFormat("%s","Edit Name :"),
             {float((GetRenderWidth()-210)/2),float((GetRenderHeight()-110)/2)},50.0,1.0,WHITE);
            for (unsigned int i = 0; i < GroupName.size(); i++)
            {
                DrawTextEx(lumberfont,TextFormat("%c",GroupName[i]),
                {float((GetRenderWidth()-290)/2)+float(i*30),float((GetRenderHeight()-10)/2)},50.0,1.0,WHITE);
            }
            if (IsKeyPressed(KEY_ESCAPE))
            {
                ExitNum -= 1;
                EditNameMode = false;
            }   
        }
        if (GroupDeleteMode)
        {
            DrawRectangle(int((GetRenderWidth()-350)/2),int((GetRenderHeight()-150)/2),350,150,{50,50,50,255});
            DrawTextEx(lumberfont,TextFormat("%s","Delete Group :"),
             {float((GetRenderWidth()-210)/2),float((GetRenderHeight()-110)/2)},50.0,1.0,WHITE);
            DrawTextEx(lumberfont,TextFormat("%s",(VertexGroup[stablenum3] + " ?").c_str()),
             {float((GetRenderWidth()-210)/2),float((GetRenderHeight()-10)/2)},50.0,1.0,WHITE);
            if (IsKeyPressed(KEY_ENTER))
            {
                VertexGroup.erase(VertexGroup.begin()+stablenum3);
                Sortvertices1();
                for (int i = 0; i < int(vertices1.size()); i++)
                {
                    if (int(vertices1[i].w) == stablenum3)
                    {
                        vertices1.erase(vertices1.begin()+i);
                        i--;
                    }
                }
                for (int i = 0; i < int(vertices1.size()); i++)
                {
                    if (int(vertices1[i].w > stablenum3))
                    {
                        vertices1[i].w -= 1;
                    }
                }
                Sortlines1();
                for (int i = 0; i < int(lines1.size()); i++)
                {
                    if (int(lines1[i].z) == stablenum3)
                    {
                        lines1.erase(lines1.begin()+i);
                        i--;
                    }
                }
                for (int i = 0; i < int(lines1.size()); i++)
                {
                    if (int(lines1[i].z > stablenum3))
                    {
                        lines1[i].z -= 1;
                    }
                }
                for (int i = 0; i < int(lines1.size()); i++)
                {
                    for (int j = 0; j < int(vertices1.size()); j++)
                    {
                        if (int(lines1[i].x) == int(vertices1[j].v))
                        {
                            boollinex = true;
                        }
                    }
                    for (int j = 0; j < int(vertices1.size()); j++)
                    {
                        if (int(lines1[i].y) == int(vertices1[j].v))
                        {
                            boolliney = true;
                        }
                    }
                    if (!(boollinex && boolliney))
                    {
                        lines1.erase(lines1.begin()+i);
                        i--;
                    }
                    boollinex = false;
                    boolliney = false;
                }
                VertexSelect.clear();
                VertexBoxIsEmpty = true;
                VertexBox = {};
                SelectedVec = -1;
                if(slide > 0)
                {
                    slide -= 1;
                }
                if (stablenum3 < GroupSelect)
                {
                    GroupSelect -= 1;
                }
                if(GroupSelect == stablenum3)
                {
                    GroupSelect = -1;
                }
                if(VertexGroup.size() == 1)
                {
                    GroupSelect = 0;
                }
                GroupDeleteMode = false;
            }
            if (IsKeyPressed(KEY_ESCAPE))
            {
                ExitNum -= 1;
                GroupDeleteMode = false;
            }      
        }

        DrawTextEx(lumberfont,TextFormat("%d %d",GetMouseX(),GetMouseY()), {10,40},50.0,1.0,WHITE);
        // FOR DEBUG                        
    }
    // FOR DEBUG
    //DrawTextEx(lumberfont,TextFormat("%.2f %.2f %.2f",camera.position.x,camera.position.y,camera.position.z),{10,100},50.0,1.0,WHITE);
    //DrawTextEx(lumberfont,TextFormat("%.2f %.2f",anglex*180/PI,anglez*180/PI),{10,200},50.0,1.0,WHITE);
    DrawTextEx(lumberfont,TextFormat("%.2f",testvec.x - testvec.y),{10,100},50.0,1.0,WHITE);
    DrawTextEx(lumberfont,TextFormat("%.2f %.2f %.2f",testvec.x,testvec.y,testvec.z),{10,150},50.0,1.0,WHITE);

    // EXIT
    if (IsKeyPressed(KEY_ESCAPE))
    {
        ExitNum += 1;
    }

    if (ExitNum == 1)
    {
        CloseMode = true;
    }
    if (CloseMode)
    {
        DrawRectangle(int((GetRenderWidth()-350)/2),int((GetRenderHeight()-150)/2),350,150,{50,50,50,255});
        DrawTextEx(lumberfont,TextFormat("%s","Exit ?"),
         {float((GetRenderWidth()-120)/2),float((GetRenderHeight()-60)/2)},70.0,1.0,WHITE);
        if (IsKeyPressed(KEY_ENTER))
        {
            EndDrawing();
            UnloadFont(lumberfont);
            UnloadTexture(texture1);
            UnloadRenderTexture(screencamera1);
            UnloadRenderTexture(screencamera2);
            CloseWindow(); 
            return 0;
        }
        if (IsKeyPressed(KEY_ESCAPE) && ExitNum == 2)
        {
            ExitNum = 0;
            CloseMode = false;
        }
    }
