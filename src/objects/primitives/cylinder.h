#pragma once

#include "primitive.h"

class Cylinder : public Primitive
{
protected:
	float radius;
	float height;

	virtual int getXMax();
	virtual int getYMax();

	virtual void getCoordinate();
	virtual void getNormalVector();

public:
	Cylinder(float radius, float height);
};