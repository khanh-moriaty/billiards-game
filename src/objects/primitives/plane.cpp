#include "primitive.h"

int Plane::getXMax() {return 2;}
int Plane::getYMax() {return 2;}

void Plane::initVertices() {
    z = +depth/2;
    Primitive::initVertices();
    z = -depth/2;
    Primitive::initVertices();
}

Plane::Plane(float width, float height, float depth) : width(width), height(height), depth(depth), Primitive()
{
    initVertices();
	initIndices(0);
	initIndices(getXMax()*getYMax());
    // Top and bottom edge
    for (int i = 0; i < getXMax()-1; i++) {
        // Top edge
        this->indices.push_back(i);
        this->indices.push_back(getXMax()*getYMax() + i);
        this->indices.push_back(getXMax()*getYMax() + i + 1);
        this->indices.push_back(i);
        this->indices.push_back(i+1);
        this->indices.push_back(getXMax()*getYMax() + i + 1);
        // Bottom edge
        this->indices.push_back(getXMax()*(getYMax()-1) + i);
        this->indices.push_back(getXMax()*(getYMax()-1) + getXMax()*getYMax() + i);
        this->indices.push_back(getXMax()*(getYMax()-1) + getXMax()*getYMax() + i + 1);
        this->indices.push_back(getXMax()*(getYMax()-1) + i);
        this->indices.push_back(getXMax()*(getYMax()-1) + i+1);
        this->indices.push_back(getXMax()*(getYMax()-1) + getXMax()*getYMax() + i + 1);
    }
    // Left and right edge
    for (int i = 0; i < getYMax()-1; i++) {
        // Left edge
        this->indices.push_back(i * getXMax());
        this->indices.push_back(getXMax()*getYMax() + i * getXMax());
        this->indices.push_back(getXMax()*getYMax() + (i + 1) * getXMax());
        this->indices.push_back(i * getXMax());
        this->indices.push_back((i+1) * getXMax());
        this->indices.push_back(getXMax()*getYMax() + (i + 1) * getXMax());
        // Right edge
        this->indices.push_back(getXMax()-1 + i * getXMax());
        this->indices.push_back(getXMax()-1 + getXMax()*getYMax() + i * getXMax());
        this->indices.push_back(getXMax()-1 + getXMax()*getYMax() + (i + 1) * getXMax());
        this->indices.push_back(getXMax()-1 + i * getXMax());
        this->indices.push_back(getXMax()-1 + (i+1) * getXMax());
        this->indices.push_back(getXMax()-1 + getXMax()*getYMax() + (i + 1) * getXMax());
    }
}

void Plane::getCoordinate() {
    xPos = (xSegment - 0.5f) * width;
    yPos = (ySegment - 0.5f) * height;
    zPos = z;
}

void Plane::getNormalVector() {
    normalVector = glm::normalize(glm::vec3(0, 0, z));
}

void Plane::generateIndices(int offset){
    //Indices that generate the mesh
    for (int i = 0; i < getYMax() - 1; i++)
    {
        for (int j = 0; j < getXMax() - 1; j++)
        {
            this->indices.push_back(offset + i * getXMax() + j);
            this->indices.push_back(offset + (i + 1) * getXMax() + j);
            this->indices.push_back(offset + (i + 1) * getXMax() + j + 1);
            this->indices.push_back(offset + i * getXMax() + j);
            this->indices.push_back(offset + (i + 1) * getXMax() + j + 1);
            this->indices.push_back(offset + i * getXMax() + j + 1);
        }
    }
}