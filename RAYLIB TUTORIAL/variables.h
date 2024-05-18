// DEFINE VALUES
#include "libs.h"

typedef struct Vector5
{
    float x;
    float y;
    float z;
    float w;
    float v;
} Vector5;

const int WindowWidth = 1920; //1366 1920
const int WindowHeight = 1080; //768 1080
int num1 = 0;
int num2 = 1;
int num3 = 0;
int num4 = 0;
int stablenum3 = 0;
int ExitNum = 0;
int KeyRepeat = 0;
int key = 0;
int GroupSelect = 0;
int stableGroupSelect = 0;
int NumOfGridLines = 3;
float GridSpacing = 1.f; 
float Snap = 1.f;
int slide = 0;
int MouseSlide = 0;
int wheel = 0;
int DimGridSwitchNumber = 0;
int CursorSwitchNumber = 0;
float MouseSens = 0.1f;
bool CursorMode = false;
bool CreateGrid = false;
bool GridSnap = false;
bool MXZone = false;
bool MYZone = false;
bool NameMode = false;
bool EditNameMode = false;
bool CloseMode = false;
bool GroupDeleteMode = false;
bool WarningMode = false;
bool CtrlZ = true;
bool boollol = true;
bool bool3 = true;
char modeArray[4] = {'C','B','D','S'};
char DimGridArray[3] = {'x','y','z'};
char mode1 = modeArray[1];
char DimGridMode = DimGridArray[0];
float StableGrid[6];
std::string string1;
int MX = 960; int MY = 540;
Ray MouseRay;
Ray StableMouseRay;
RayCollision MouseRayCollision;
float ETime;
float StableETime;
float StableETime2;
int DrawDelay = 2;
//int test = 0;

std::vector<char> GroupName;

//float window1x = 1600.f; float window1y = 360.f; float window1w = 320.f; float window1h = 720.f;
float bewindowy1 = 400.f;
int color1 = 120; int color2 = 120; int color3 = 255; int color4 = 100;

std::vector<Vector5> vertices1;

// 1 : List

// --------------------- NORMAL RECTANGLE ---------------------

std::vector<Vector4> UIWindowRect1 =
{
    {1600.f,360.f,320.f,720.f}
};

std::vector<Vector4> UIWindowRectValue1 =
{
    {1600.f,360.f,320.f,720.f}
};

std::vector<Vector4> UIWindowColor1 =
{
    {100,100,100,150}
};

// --------------------- BEHAVIOUR RECTANGLE ---------------------

// 1 : Add Group , 2 : Group List Slide , 3 : Group Remove Button , 4 : Group Edit Name Button , 5 : Group Select
std::vector<Vector4> UIWindowBeRect1 =
{
    {1605.f,395.f,30.f,30.f},
    {1880.f,400.f,35.f,200.f},
    {1640.f,422.f,16.f,16.f},
    {1640.f,442.f,16.f,16.f},
    {1640.f,420.f,280.f,40.f}
};

std::vector<Vector4> UIWindowBeRectValue1 =
{
    {1605.f,395.f,30.f,30.f},
    {1880.f,400.f,35.f,100.f},
    {1640.f,422.f,16.f,16.f},
    {1640.f,442.f,16.f,16.f},
    {1640.f,420.f,280.f,40.f}
};

std::vector<Vector4> UIWindowBeColor1 =
{
    {120,120,120,255},
    {120,120,120,255},
    {255,100,100,255},
    {120,120,120,255},
    {0,0,0,100}
};

// ---------------------------------------------------------------

// UI WINDOW BEHAVIOUR RECTANGLE
std::vector<Vector4> UIWindowBeRect2;

std::vector<Vector4> UIWindowBeColor2;

std::vector<Vector4> UIWindowRect2;

std::vector<Vector4> UIWindowColor2;

std::vector<std::string> VertexGroup;
Vector5 sort;
Vector2 Point;

#include "variables2.h"
