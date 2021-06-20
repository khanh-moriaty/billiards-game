#pragma once

#include "primitive.h"

class Cylinder : public Primitive
{
private:
	static const int X_SEGMENTS;
	static const int Y_SEGMENTS;

protected:
    virtual void getCoordinate(float& xPos, float& yPos, float& zPos, float xSegment, float ySegment, float radius, float height);
public:
	Cylinder(float radius, float height);
};