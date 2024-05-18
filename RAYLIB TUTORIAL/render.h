if (RenderMode && !CursorMode && !CloseMode)
{
    DrawRectangle(0,0,GetRenderWidth(),GetRenderHeight(),{0,0,0,255});
    if (!FinalRenderMode)
    {
        for (int i = 0; i < int(lines1.size()); i++)
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
                    RenderLineX = GetWorldToScreenEx({vertices1[xval].x,vertices1[xval].y,vertices1[xval].z},camera,GetRenderWidth(),GetRenderHeight());
                    RenderLineY = GetWorldToScreenEx({vertices1[yval].x,vertices1[yval].y,vertices1[yval].z},camera,GetRenderWidth(),GetRenderHeight());
                    DrawLineV(RenderLineX,RenderLineY,{255,255,255,255});
                    RenderCircleX = int((RenderLineX.x + RenderLineY.x)/2);
                    RenderCircleY = int((RenderLineX.y + RenderLineY.y)/2);
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !shit)
                    {
                        if (GetMouseX() >= RenderCircleX - 7 && GetMouseX() <= RenderCircleX + 7 &&
                         GetMouseY() >= RenderCircleY - 7 && GetMouseY() <= RenderCircleY + 7)
                        {
                            SelectedRenderCircle = int(lines1[i].w);
                            shit = true;
                        }
                        else
                        {
                            SelectedRenderCircle = -1;
                        }
                    }
                    if (SelectedRenderCircle == int(lines1[i].w))
                    {
                        DrawCircle(RenderCircleX,RenderCircleY,7.f,{100,100,100,255});
                    }
                    else
                    {
                        DrawCircle(RenderCircleX,RenderCircleY,7.f,{150,150,150,255});
                    }
                    xval = -1;
                    yval = -1;
                    break;
                }
            }
        }
        shit = false;
        if (SelectedRenderCircle > -1)
        {
            
        }
    }

    DrawTextEx(lumberfont, TextFormat("%s %d","FinalRender : ",FinalRenderMode), {10,10}, 30.0, 2.0, WHITE);
}