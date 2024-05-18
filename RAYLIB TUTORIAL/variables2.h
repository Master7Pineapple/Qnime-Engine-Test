#include "libs.h"

typedef struct Line
{
    float x;
    float y;
    int z;
    int w;
    int rotation;   
} Line;

int xval = -1;
int yval = -1;
int numline1 = 0;
int selposx1, selposx2, selposy1, selposy2;
Vector2 prevec1;
std::vector<Vector3> vec1;
std::vector<int> vec2;
Vector2 SelectOrigin;
Line sort2;
BoundingBox VertexBox;
bool VertexBoxIsEmpty;
bool bool1 = true;
bool boollinex = false;
bool boolliney = false;
char storedArrayMode = 'C';
RayCollision MouseRayCollision2;

std::vector<Line> lines1;
std::vector<Vector3> Points;

std::vector<int> VertexSelect;
int SelectedVec = 0;


bool RenderMode = false;
bool FinalRenderMode = false;
bool shit = false;

Vector2 RenderLineX;
Vector2 RenderLineY;
int RenderCircleX;
int RenderCircleY;
int SelectedRenderCircle = -1;

Vector3 testvec;
