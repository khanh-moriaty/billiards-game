#include "primitive.h"
#include "cylinder.h"

int Cylinder::getXMax() {return 50;}
int Cylinder::getYMax() {return 2;}

Cylinder::Cylinder(float radius, float height) : radius(radius), height(height), Primitive() {
    initVertices();
	initIndices(0);
}

void Cylinder::getNormalVector() {
    normalVector = glm::normalize(glm::vec3(xPos, 0, zPos));
}

void Cylinder::getCoordinate()
{
    xPos = std::cos(xSegment * 2.0f * PI) * radius;
    yPos = ySegment * height;
    zPos = std::sin(xSegment * 2.0f * PI) * radius;
}