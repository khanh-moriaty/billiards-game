#include "pool_table_primitive.h"

using namespace PoolTablePrimitive;

int PoolTableFace::getXMax() { return 150; }
int PoolTableFace::getYMax() { return 2; }

PoolTableFace::PoolTableFace(float width, float height, float holeRadius) : width(width), height(height), holeRadius(holeRadius), Primitive()
{
    initVertices();
    initIndices();
}

void PoolTableFace::getNormalVector() { normalVector = glm::vec3(0.f, 1.f, 0.f); }

void PoolTableFace::getCoordinate()
{
    // y coordinate is the same across Table face
    yPos = 0.f;
    
    // Table face has 3 holes on each long edge, hence 3 conditions for xPos
    if (xSegment < 1 / 3)
    {
        xPos = sin(xSegment * 3 * PI / 2) * holeRadius - width / 2;
        zPos = cos(xSegment * 3 * PI / 2) * holeRadius - height / 2;
    }
    else if (xSegment < 2 / 3)
    {
        xPos = -cos((xSegment * 3 - 1) * PI) * holeRadius;
        zPos = sin((xSegment * 3 - 1) * PI) * holeRadius - height / 2;
    }
    else
    {
        xPos = -cos((xSegment * 3 - 2) * PI / 2) * holeRadius + width / 2;
        zPos = sin((xSegment * 3 - 2) * PI / 2) * holeRadius - height / 2;
    }

    // z-coordinates are flipped for y == 1
    if (ySegment > 1 / 2)
    {
        zPos *= -1;
    }
}