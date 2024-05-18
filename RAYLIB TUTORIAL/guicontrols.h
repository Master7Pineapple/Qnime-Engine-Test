
    if (CursorMode)
    {   
        MX = GetMouseX();
        MY = GetMouseY();
        // SLIDE BUTTON
        if (MX >= int(UIWindowRect1.at(0).x) && MX <= (int(UIWindowRect1.at(0).x))+(int(UIWindowRect1.at(0).z)) &&
         MY >= int(UIWindowRect1.at(0).y+60.f) && MY <= (int(UIWindowRect1.at(0).y+60.f))+(int(UIWindowRect1.at(0).w)))
        {
            if (int(GetMouseWheelMove()) < 0 && VertexGroup.size() > 16 &&
             (VertexGroup.size() - 16 - slide) > 0)
            {             
                slide += 1;
                UIWindowBeRect1.at(1).y += (GetRenderHeight()-(GetRenderHeight()-680)-UIWindowBeRect1.at(1).w)/float(VertexGroup.size()-16);
                if (UIWindowBeRect1.at(1).y > (float(GetRenderHeight()) - UIWindowBeRect1.at(1).w))
                {
                    UIWindowBeRect1.at(1).y = float(float(GetRenderHeight()) - UIWindowBeRect1.at(1).w);
                }                         
            }

            if (int(GetMouseWheelMove()) > 0 && VertexGroup.size() > 16 &&
             (VertexGroup.size() - 16 + slide) > (VertexGroup.size() - 16))
            {      
                slide -= 1;
                UIWindowBeRect1.at(1).y -= (GetRenderHeight()-(GetRenderHeight()-680)-UIWindowBeRect1.at(1).w)/float(VertexGroup.size()-16);
                if (UIWindowBeRect1.at(1).y < (GetRenderHeight()-680))
                {
                    UIWindowBeRect1.at(1).y = (GetRenderHeight()-680);
                }                
            }
            num3 = int((MY - (GetRenderHeight()-int(UIWindowRect1[0].w))-60)/40) + slide;
            if ((unsigned)num3 >= VertexGroup.size())
            {
                num3 = -1;
            }
            if (MX >= int(UIWindowRect1.at(0).x+57.f) && MX <= (int(UIWindowRect1.at(0).x))+(int(UIWindowRect1.at(0).z)) 
             && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                GroupSelect = num3;
            }
        }
        else
        {
            num3 = -1;
        }

        if (VertexGroup.size() > 16)
        {
            if (MX >= int(UIWindowBeRect1.at(1).x) && MX <= (int(UIWindowBeRect1.at(1).x))+(int(UIWindowBeRect1.at(1).z)) &&
             MY >= int(UIWindowBeRect1.at(1).y) && MY <= (int(UIWindowBeRect1.at(1).y))+(int(UIWindowBeRect1.at(1).w)))
            {
                UIWindowBeColor1.at(1).x = color2 + 50;
                if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
                {   
                    if (num2 == 1)
                    {
                        MouseSlide = MY-(int(UIWindowBeRect1.at(1).y));
                        num2 = 0;
                    }        
                    UIWindowBeColor1.at(1).x = color2 + 100;
                    if (UIWindowBeRect1.at(1).y <= (float(GetRenderHeight()) - UIWindowBeRect1.at(1).w) && UIWindowBeRect1.at(1).y >= (GetRenderHeight()-680))
                    {
                        UIWindowBeRect1.at(1).y = float(MY) - float(MouseSlide);
                    }

                    if (UIWindowBeRect1.at(1).y > (float(GetRenderHeight()) - UIWindowBeRect1.at(1).w))
                    {
                        UIWindowBeRect1.at(1).y = float(float(GetRenderHeight()) - UIWindowBeRect1.at(1).w);
                    }

                    if (UIWindowBeRect1.at(1).y < (GetRenderHeight()-680))
                    {
                        UIWindowBeRect1.at(1).y = (GetRenderHeight()-680);
                    } 
                    
                    if (VertexGroup.size() > 16)
                    {
                        slide = int(round((UIWindowBeRect1.at(1).y-(GetRenderHeight()-680))/
                         ((GetRenderHeight()-(GetRenderHeight()-680)-UIWindowBeRect1.at(1).w)/float(VertexGroup.size()-16))));
                    } 
                }
                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
                {
                    UIWindowBeColor1.at(1).x = color2 + 50;
                    num2 = 1;
                } 
            }
            else
            {
                UIWindowBeColor1.at(1).x = color2;
            }    
        }   

        // ADD BUTTON
        if (MX >= int(UIWindowBeRect1.at(0).x) && MX <= (int(UIWindowBeRect1.at(0).x))+(int(UIWindowBeRect1.at(0).z)) &&
         MY >= int(UIWindowBeRect1.at(0).y) && MY <= (int(UIWindowBeRect1.at(0).y))+(int(UIWindowBeRect1.at(0).w)))
        {
            UIWindowBeColor1.at(0).x = color1 + 50;
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {             
                UIWindowBeColor1.at(0).x = color1 + 100;
                NameMode = true;
            }
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            {
                UIWindowBeColor1.at(0).x = color1 + 50;
            }
        }
        else if (IsKeyPressed(KEY_N) && !NameMode)
        {
            NameMode = true;
            bool3 = false;
        }
        else
        {
            UIWindowBeColor1.at(0).x = color1;
        }
       
        // Name Mode
        if (NameMode)
            {
                if (bool3)
                {
                    key = GetCharPressed();
                }
                bool3 = true;
                if ((key >= 32) && (key <= 125) && GroupName.size() < 10)
                {
                    GroupName.push_back(char(key));
                    key = 0;
                }
                if (IsKeyPressed(KEY_BACKSPACE) && GroupName.size() > 0)
                {
                    GroupName.pop_back();
                    StableETime = ETime;           
                }
                if (IsKeyDown(KEY_BACKSPACE) && GroupName.size() > 0 && ETime - StableETime > 0.3f)
                {
                    GroupName.pop_back();             
                }
                if (IsKeyPressed(KEY_ENTER))
                {
                    if (GroupName.size() == 0)
                    {
                        VertexGroup.push_back("Group " + std::to_string(VertexGroup.size()+1));
                    }
                    if (GroupName.size() > 0)
                    {
                        for (unsigned i = 0; i < GroupName.size(); i++)
                        {
                            string1 += GroupName[i];
                        }
                        VertexGroup.push_back(string1);
                        GroupName.clear();
                        string1.clear();
                    }
                    NameMode = false;
                }
            }
        
        // Edit Name Mode
        if (EditNameMode)
        {
            key = GetCharPressed();
            if ((key >= 32) && (key <= 125) && GroupName.size() < 10)
            {
                GroupName.push_back(char(key));
                key = 0;
            }
            if (IsKeyPressed(KEY_BACKSPACE) && GroupName.size() > 0)
            {
                GroupName.pop_back();
                StableETime = ETime;             
            }
            if (IsKeyDown(KEY_BACKSPACE) && GroupName.size() > 0 && ETime - StableETime > 0.3f)
            {
                GroupName.pop_back();             
            }
            if (IsKeyPressed(KEY_ENTER))
            {
                if (GroupName.size() == 0)
                {
                    EditNameMode = false;
                }
                if (GroupName.size() > 0)
                {
                    for (unsigned i = 0; i < GroupName.size(); i++)
                    {
                        string1 += GroupName[i];
                    }
                    VertexGroup[stablenum3] = string1;
                    GroupName.clear();
                    string1.clear();
                }
                EditNameMode = false;
            }
        }
        // DELETE - EDIT GROUP BUTTON
        if (MX >= int(UIWindowRect1.at(0).x) && MX <= (int(UIWindowRect1.at(0).x))+(int(UIWindowRect1.at(0).z)) &&
         MY >= int(UIWindowRect1.at(0).y+60.f) && MY <= (int(UIWindowRect1.at(0).y))+(int(UIWindowRect1.at(0).w)))
        {
            if (MX >= int(UIWindowBeRect1.at(2).x) && MX <= (int(UIWindowBeRect1.at(2).x))+(int(UIWindowBeRect1.at(2).z)) &&
            MY >= int(UIWindowBeRect1.at(2).y+((num3-slide)*40)) &&
            MY <= (int(UIWindowBeRect1.at(2).y+((num3-slide)*40)))+(int(UIWindowBeRect1.at(2).w)))
            {
                UIWindowBeColor1.at(2).x = color3 - 50;
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {             
                    UIWindowBeColor1.at(2).x = color3 - 100;
                    stablenum3 = num3;
                    GroupDeleteMode = true;             
                }
                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
                {
                    UIWindowBeColor1.at(2).x = color3 - 50;
                }
            }
            else
            {
                UIWindowBeColor1.at(2).x = color3;
            }

            if (MX >= int(UIWindowBeRect1.at(3).x) && MX <= (int(UIWindowBeRect1.at(3).x))+(int(UIWindowBeRect1.at(3).z)) &&
            MY >= int(UIWindowBeRect1.at(3).y+((num3-slide)*40)) &&
            MY <= (int(UIWindowBeRect1.at(3).y+((num3-slide)*40)))+(int(UIWindowBeRect1.at(3).w)))
            {
                UIWindowBeColor1.at(3).x = color2 + 50;
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {             
                    UIWindowBeColor1.at(3).x = color2 + 100;
                    stablenum3 = num3;
                    EditNameMode = true;                
                }
                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
                {
                    UIWindowBeColor1.at(3).x = color2 + 50;
                }
            }
            else
            {
                UIWindowBeColor1.at(3).x = color2;
            }
        }
    }
       