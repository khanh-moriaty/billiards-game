#pragma once

#include <objects/primitives/primitive.h>

namespace PoolTablePrimitive {
    extern const float TABLE_WIDTH; // Table width is the longer edge. Table resolution is 1:2
    extern const float TABLE_HEIGHT; // Height of the table leg.
    extern const float TABLE_HOLE_RADIUS;
    extern const float TABLE_HOLE_HEIGHT;

    class PoolTableFace;
    class PoolTableBody;
    class PoolTableHole;
    class PoolTableLeg;
}

class PoolTablePrimitive::PoolTableFace: public Primitive{
protected:
	float width;
	float height;
	float holeRadius;

	virtual int getXMax();
	virtual int getYMax();

	virtual void getCoordinate();
	virtual void getNormalVector();

public:
    PoolTableFace(float width, float height, float holeRadius);
};