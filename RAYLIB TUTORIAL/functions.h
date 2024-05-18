#include "libs.h"

void Draw3DBillboardRec(Camera camera, Texture2D texture, Rectangle source, Vector3 position, Vector2 size, Color tint)
{
    rlPushMatrix();

    // get the camera view matrix
    Matrix mat =MatrixInvert(MatrixLookAt(camera.position, camera.target, camera.up));
    // peel off just the rotation
    Quaternion quat = QuaternionFromMatrix(mat);
    mat = QuaternionToMatrix(quat);

    // apply just the rotation
    rlMultMatrixf(MatrixToFloat(mat));

    // translate backwards in the inverse rotated matrix to put the item where it goes in world space
    position = Vector3Transform(position, MatrixInvert(mat));
    rlTranslatef(position.x, position.y, position.z);

    // draw the billboard
    float width = size.x / 2;
    float height = size.y / 2;

    rlCheckRenderBatchLimit(6);

    rlSetTexture(texture.id);

    // draw quad
    rlBegin(RL_QUADS);
    rlColor4ub(tint.r, tint.g, tint.b, tint.a);
    // Front Face
    rlNormal3f(0.0f, 0.0f, 1.0f);                  // Normal Pointing Towards Viewer

    rlTexCoord2f((float)source.x / texture.width, (float)(source.y + source.height) / texture.height);
    rlVertex3f(-width, -height, 0);  // Bottom Left Of The Texture and Quad
    
    rlTexCoord2f((float)(source.x + source.width) / texture.width, (float)(source.y + source.height) / texture.height);
    rlVertex3f(+width, -height, 0);  // Bottom Right Of The Texture and Quad
   
    rlTexCoord2f((float)(source.x + source.width) / texture.width, (float)source.y / texture.height);
    rlVertex3f(+width, +height, 0);  // Top Right Of The Texture and Quad

    rlTexCoord2f((float)source.x / texture.width, (float)source.y / texture.height);
    rlVertex3f(-width, +height, 0);  // Top Left Of The Texture and Quad

    rlEnd();
    rlSetTexture(0);
    rlPopMatrix();
}

void Draw3DBillboard(Camera camera, Texture2D texture, Vector3 position, float size, Color tint)
{
    Draw3DBillboardRec(camera, texture, (Rectangle){ 0,0,(float)texture.width,(float)texture.height }, position, (Vector2){ size,size }, tint);
}

void DrawDimGrid(Vector3 position,float spacing,int NumOfLines, Color tint,char D)
{
    if (D == 'x' || D == 'X')
    {
        for (int i = 1-NumOfLines; i < NumOfLines; i++)
        {
            DrawLine3D({position.x+(float(i)*spacing),position.y,position.z+(float(1-NumOfLines)*spacing)},{position.x+(float(i)*spacing),position.y,position.z-(float(1-NumOfLines)*spacing)},tint);
            DrawLine3D({position.x+(float(1-NumOfLines)*spacing),position.y,position.z+(float(i)*spacing)},{position.x-(float(1-NumOfLines)*spacing),position.y,position.z+(float(i)*spacing)},tint);
            if (i == 0)
            {
                DrawLine3D({position.x+(float(i)*spacing),position.y,position.z+(float(1-NumOfLines)*spacing)},{position.x+(float(i)*spacing),position.y,position.z-(float(1-NumOfLines)*spacing)},WHITE);
                DrawLine3D({position.x+(float(1-NumOfLines)*spacing),position.y,position.z+(float(i)*spacing)},{position.x-(float(1-NumOfLines)*spacing),position.y,position.z+(float(i)*spacing)},WHITE);
            }
        }
    }

    if (D == 'y' || D == 'Y')
    {
        for (int i = 1-NumOfLines; i < NumOfLines; i++)
        {
            DrawLine3D({position.x+(float(i)*spacing),position.y+(float(1-NumOfLines)*spacing),position.z},{position.x+(float(i)*spacing),position.y-(float(1-NumOfLines)*spacing),position.z},tint);
            DrawLine3D({position.x+(float(1-NumOfLines)*spacing),position.y+(float(i)*spacing),position.z},{position.x-(float(1-NumOfLines)*spacing),position.y+(float(i)*spacing),position.z},tint);
            if (i == 0)
            {
                DrawLine3D({position.x+(float(i)*spacing),position.y+(float(1-NumOfLines)*spacing),position.z},{position.x+(float(i)*spacing),position.y-(float(1-NumOfLines)*spacing),position.z},WHITE);
                DrawLine3D({position.x+(float(1-NumOfLines)*spacing),position.y+(float(i)*spacing),position.z},{position.x-(float(1-NumOfLines)*spacing),position.y+(float(i)*spacing),position.z},WHITE);
            }
        }   
    }

    if (D == 'z' || D == 'Z')
    {   
        for (int i = 1-NumOfLines; i < NumOfLines; i++)
        {
            DrawLine3D({position.x,position.y+(float(i)*spacing),position.z+(float(1-NumOfLines)*spacing)},{position.x,position.y+(float(i)*spacing),position.z-(float(1-NumOfLines)*spacing)},tint);
            DrawLine3D({position.x,position.y+(float(1-NumOfLines)*spacing),position.z+(float(i)*spacing)},{position.x,position.y-(float(1-NumOfLines)*spacing),position.z+(float(i)*spacing)},tint);
            if (i == 0)
            {
                DrawLine3D({position.x,position.y+(float(i)*spacing),position.z+(float(1-NumOfLines)*spacing)},{position.x,position.y+(float(i)*spacing),position.z-(float(1-NumOfLines)*spacing)},WHITE);
                DrawLine3D({position.x,position.y+(float(1-NumOfLines)*spacing),position.z+(float(i)*spacing)},{position.x,position.y-(float(1-NumOfLines)*spacing),position.z+(float(i)*spacing)},WHITE);
            }
        }
    }
}

void Sortvertices1()
{
    for (int jj = 0; jj < int(vertices1.size()); jj++)
    {
        for (int ii = 0; ii < int(vertices1.size()-1); ii++)
        {
            if (vertices1[ii+1].w < vertices1[ii].w)
            {
                sort = vertices1[ii];
                vertices1[ii] = vertices1[ii+1];
                vertices1[ii+1] = sort;
            }
        }
    }
}

void Sortlines1()
{
    for (int jj = 0; jj < int(lines1.size()); jj++)
    {
        for (int ii = 0; ii < int(lines1.size()-1); ii++)
        {
            if (lines1[ii+1].z < lines1[ii].z)
            {
                sort2 = lines1[ii];
                lines1[ii] = lines1[ii+1];
                lines1[ii+1] = sort2;
            }
        }
    }
}

void DrawRectangle2(int posx1, int posy1, int posx2, int posy2,Color color)
{
    if (posx1 < posx2 && posy1 < posy2)
    {
        DrawRectangle(posx1,posy1,posx2-posx1,posy2-posy1,color);
        selposx1 = posx1;
        selposx2 = posx1 + posx2-posx1;
        selposy1 = posy1;
        selposy2 = posy1 + posy2-posy1;
    }
    else if (posx1 < posx2 && posy1 > posy2)
    {
        DrawRectangle(posx1,posy2,posx2-posx1,posy1-posy2,color);
        selposx1 = posx1;
        selposx2 = posx1 + posx2-posx1;
        selposy1 = posy2;
        selposy2 = posy2 + posy1-posy2;
    }
    else if (posx1 > posx2 && posy1 > posy2)
    {
        DrawRectangle(posx2,posy2,posx1-posx2,posy1-posy2,color);
        selposx1 = posx2;
        selposx2 = posx2 + posx1-posx2;
        selposy1 = posy2;
        selposy2 = posy2 + posy1-posy2;
    }
    else if (posx1 > posx2 && posy1 < posy2)
    {
        DrawRectangle(posx2,posy1,posx1-posx2,posy2-posy1,color);
        selposx1 = posx2;
        selposx2 = posx2 + posx1-posx2;
        selposy1 = posy1;
        selposy2 = posy1 + posy2-posy1;
    }
}

Vector3 rotate_point(Vector3 axis_start, Vector3 axis_end, Vector3 point, float angle) {
    // Calculate the axis vector
    Vector3 axis = {
        axis_end.x - axis_start.x,
        axis_end.y - axis_start.y,
        axis_end.z - axis_start.z
    };

    // Normalize the axis vector
    float magnitude = sqrtf(axis.x * axis.x + axis.y * axis.y + axis.z * axis.z);
    axis.x /= magnitude;
    axis.y /= magnitude;
    axis.z /= magnitude;

    // Move the point to the start of the axis
    point.x -= axis_start.x;
    point.y -= axis_start.y;
    point.z -= axis_start.z;

    // Rotate the point using Rodrigues' rotation formula
    float cos_angle = cosf(angle);
    float sin_angle = sinf(angle);
    float dot_product = point.x * axis.x + point.y * axis.y + point.z * axis.z;
    Vector3 cross_product = {
        point.y * axis.z - point.z * axis.y,
        point.z * axis.x - point.x * axis.z,
        point.x * axis.y - point.y * axis.x
    };

    Vector3 new_point = {
        point.x * cos_angle + cross_product.x * sin_angle + axis.x * dot_product * (1 - cos_angle),
        point.y * cos_angle + cross_product.y * sin_angle + axis.y * dot_product * (1 - cos_angle),
        point.z * cos_angle + cross_product.z * sin_angle + axis.z * dot_product * (1 - cos_angle)
    };
    testvec = cross_product;

    // Move the point back to its original position
    new_point.x += axis_start.x;
    new_point.y += axis_start.y;
    new_point.z += axis_start.z;

    return new_point;
}