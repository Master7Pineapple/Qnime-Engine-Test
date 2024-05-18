
if (mode1 == modeArray[3] && !CursorMode && !CloseMode)
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        SelectOrigin = {float(GetMouseX()),float(GetMouseY())};
        vec1.clear();
        vec2.clear();
    }
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        DrawRectangle2(int(SelectOrigin.x),int(SelectOrigin.y),GetMouseX(),GetMouseY(),{255,0,0,100});
    }
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    {
        for (int i = 0; i < int(vertices1.size()); i++)
        {
            if (int(vertices1[i].w) == GroupSelect)
            {
                prevec1 = GetWorldToScreenEx({vertices1[i].x,vertices1[i].y,vertices1[i].z},camera,GetRenderWidth(),GetRenderHeight());
                vec1.push_back({prevec1.x,prevec1.y,vertices1[i].v});
            }
        }
        for (int i = 0; i < int(vec1.size()); i++)
        {
            if (int(vec1[i].x) >= selposx1 && int(vec1[i].x) <= selposx2
             && int(vec1[i].y) >= selposy1 && int(vec1[i].y) <= selposy2)
            {
                vec2.push_back(int(vec1[i].z));
            }
        }
    }
    if (IsKeyPressed(KEY_BACKSPACE))
    {
        if (vec2.size() > 0)
        {
            for (int i = 0; i < int(vertices1.size()); i++)
            {
                if (int(vertices1[i].w) == GroupSelect)
                {
                    for (int j = 0; j < int(vec2.size()); j++)
                    {
                        if (int(vertices1[i].v) == vec2[j])
                        {
                            vertices1.erase(vertices1.begin()+i);
                        }
                        for (int k = 0; k < int(lines1.size()); k++)
                        {
                            if (int(lines1[k].x) == vec2[j])
                            {
                                lines1.erase(lines1.begin()+k);
                            }
                        }
                        for (int k = 0; k < int(lines1.size()); k++)
                        {
                            if (int(lines1[k].y) == vec2[j])
                            {
                                lines1.erase(lines1.begin()+k);
                            }
                        }
                    }
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
        }
    }
    else if (IsKeyPressed(KEY_DOWN))
    {
        if (vec2.size() > 0)
        {
            for (int i = 0; i < int(vertices1.size()); i++)
            {
                if (int(vertices1[i].w) == GroupSelect)
                {
                    for (int j = 0; j < int(vec2.size()); j++)
                    {
                        if (int(vertices1[i].v) == vec2[j])
                        { 
                            vertices1[i].z += 0.25f;
                        }
                    }
                }
            }
        }
    }
    else if (IsKeyPressed(KEY_UP))
    {
        if (vec2.size() > 0)
        {
            for (int i = 0; i < int(vertices1.size()); i++)
            {
                if (int(vertices1[i].w) == GroupSelect)
                {
                    for (int j = 0; j < int(vec2.size()); j++)
                    {
                        if (int(vertices1[i].v) == vec2[j])
                        { 
                            vertices1[i].z -= 0.25f;
                        }
                    }
                }
            }
        }
    }
    else if (IsKeyPressed(KEY_RIGHT))
    {
        if (vec2.size() > 0)
        {
            for (int i = 0; i < int(vertices1.size()); i++)
            {
                if (int(vertices1[i].w) == GroupSelect)
                {
                    for (int j = 0; j < int(vec2.size()); j++)
                    {
                        if (int(vertices1[i].v) == vec2[j])
                        { 
                            vertices1[i].x += 0.25f;
                        }
                    }
                }
            }
        }
    }
    else if (IsKeyPressed(KEY_LEFT))
    {
        if (vec2.size() > 0)
        {
            for (int i = 0; i < int(vertices1.size()); i++)
            {
                if (int(vertices1[i].w) == GroupSelect)
                {
                    for (int j = 0; j < int(vec2.size()); j++)
                    {
                        if (int(vertices1[i].v) == vec2[j])
                        { 
                            vertices1[i].x -= 0.25f;
                        }
                    }
                }
            }
        }
    }
    else if (IsKeyPressed(KEY_SPACE))
    {
        if (vec2.size() > 0)
        {
            for (int i = 0; i < int(vertices1.size()); i++)
            {
                if (int(vertices1[i].w) == GroupSelect)
                {
                    for (int j = 0; j < int(vec2.size()); j++)
                    {
                        if (int(vertices1[i].v) == vec2[j])
                        { 
                            vertices1[i].y += 0.25f;
                        }
                    }
                }
            }
        }
    }
    else if (IsKeyPressed(KEY_Z))
    {
        if (vec2.size() > 0)
        {
            for (int i = 0; i < int(vertices1.size()); i++)
            {
                if (int(vertices1[i].w) == GroupSelect)
                {
                    for (int j = 0; j < int(vec2.size()); j++)
                    {
                        if (int(vertices1[i].v) == vec2[j])
                        { 
                            vertices1[i].y -= 0.25f;
                        }
                    }
                }
            }
        }
    }

}
