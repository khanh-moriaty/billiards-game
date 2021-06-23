#include "primitive.h"

int Sphere::getXMax() { return 50; }
int Sphere::getYMax() { return 50; }

Sphere::Sphere(float radius) : radius(radius), Primitive() {
	initVertices();
	initIndices(0);
}

void Sphere::getCoordinate() {
	xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI) * radius;
	yPos = - std::cos(ySegment * PI) * radius;
	zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI) * radius;
}

void Sphere::getNormalVector() {
	normalVector = glm::normalize(glm::vec3(xPos, yPos, zPos));
}