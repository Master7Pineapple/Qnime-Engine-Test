

if (IsWindowResized())
{
    for (unsigned int i = 0; i < UIWindowRect1.size(); i++)
    {
        UIWindowRect1[i].x = float(GetRenderWidth()) - (float(WindowWidth) - UIWindowRectValue1[i].x);
        UIWindowRect1[i].y = float(GetRenderHeight()) - (float(WindowHeight) - UIWindowRectValue1[i].y);
    }
    for (unsigned int i = 0; i < UIWindowBeRect1.size(); i++)
    {
        UIWindowBeRect1[i].x = float(GetRenderWidth()) - (float(WindowWidth) - UIWindowBeRectValue1[i].x);
        UIWindowBeRect1[i].y = float(GetRenderHeight()) - (float(WindowHeight) - UIWindowBeRectValue1[i].y);
    }
}
