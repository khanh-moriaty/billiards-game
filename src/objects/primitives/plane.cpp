#include "primitive.h"

const int Plane::X_SEGMENTS = 2;
const int Plane::Y_SEGMENTS = 2;

Plane::Plane(float width, float height, float depth) : Primitive()
{
    generateFace(width, height, +depth/2);
    generateFace(width, height, -depth/2);
    generateIndices(0);
    generateIndices(X_SEGMENTS*Y_SEGMENTS);

    // Connect 2 faces

    // Top and bottom edge
    for (int i = 0; i < X_SEGMENTS-1; i++) {
        // Top edge
        this->indices.push_back(i);
        this->indices.push_back(X_SEGMENTS*Y_SEGMENTS + i);
        this->indices.push_back(X_SEGMENTS*Y_SEGMENTS + i + 1);
        this->indices.push_back(i);
        this->indices.push_back(i+1);
        this->indices.push_back(X_SEGMENTS*Y_SEGMENTS + i + 1);
        // Bottom edge
        this->indices.push_back(X_SEGMENTS*(Y_SEGMENTS-1) + i);
        this->indices.push_back(X_SEGMENTS*(Y_SEGMENTS-1) + X_SEGMENTS*Y_SEGMENTS + i);
        this->indices.push_back(X_SEGMENTS*(Y_SEGMENTS-1) + X_SEGMENTS*Y_SEGMENTS + i + 1);
        this->indices.push_back(X_SEGMENTS*(Y_SEGMENTS-1) + i);
        this->indices.push_back(X_SEGMENTS*(Y_SEGMENTS-1) + i+1);
        this->indices.push_back(X_SEGMENTS*(Y_SEGMENTS-1) + X_SEGMENTS*Y_SEGMENTS + i + 1);
    }
    // Left and right edge
    for (int i = 0; i < Y_SEGMENTS-1; i++) {
        // Left edge
        this->indices.push_back(i * X_SEGMENTS);
        this->indices.push_back(X_SEGMENTS*Y_SEGMENTS + i * X_SEGMENTS);
        this->indices.push_back(X_SEGMENTS*Y_SEGMENTS + (i + 1) * X_SEGMENTS);
        this->indices.push_back(i * X_SEGMENTS);
        this->indices.push_back((i+1) * X_SEGMENTS);
        this->indices.push_back(X_SEGMENTS*Y_SEGMENTS + (i + 1) * X_SEGMENTS);
        // Right edge
        this->indices.push_back(X_SEGMENTS-1 + i * X_SEGMENTS);
        this->indices.push_back(X_SEGMENTS-1 + X_SEGMENTS*Y_SEGMENTS + i * X_SEGMENTS);
        this->indices.push_back(X_SEGMENTS-1 + X_SEGMENTS*Y_SEGMENTS + (i + 1) * X_SEGMENTS);
        this->indices.push_back(X_SEGMENTS-1 + i * X_SEGMENTS);
        this->indices.push_back(X_SEGMENTS-1 + (i+1) * X_SEGMENTS);
        this->indices.push_back(X_SEGMENTS-1 + X_SEGMENTS*Y_SEGMENTS + (i + 1) * X_SEGMENTS);
    }
}

void Plane::generateFace(float width, float height, float z)
{
    for (int y = 0; y < Y_SEGMENTS; y++)
    {
        for (int x = 0; x < X_SEGMENTS; x++)
        {
            float xSegment = (float)x / (float)(X_SEGMENTS - 1);
            float ySegment = (float)y / (float)(Y_SEGMENTS - 1);
            float xPos = (xSegment - 0.5f) * width;
            float yPos = (ySegment - 0.5f) * height;
            float zPos = z;
            glm::vec3 pos = glm::vec3(xPos, yPos, zPos);
            glm::vec3 color = glm::vec3(0.f, 0.f, 0.f);
            glm::vec2 tex = glm::vec2(-xSegment, ySegment);
            glm::vec3 nor = glm::normalize(glm::vec3(0, 0, z));
            Vertex temp;
            temp.position = pos;
            temp.color = color;
            temp.texcoord = tex;
            temp.normal = nor;
            this->vertices.push_back(temp);
        }
    }
}

void Plane::generateIndices(int offset){
    //Indices that generate the mesh
    for (int i = 0; i < Y_SEGMENTS - 1; i++)
    {
        for (int j = 0; j < X_SEGMENTS - 1; j++)
        {
            this->indices.push_back(offset + i * X_SEGMENTS + j);
            this->indices.push_back(offset + (i + 1) * X_SEGMENTS + j);
            this->indices.push_back(offset + (i + 1) * X_SEGMENTS + j + 1);
            this->indices.push_back(offset + i * X_SEGMENTS + j);
            this->indices.push_back(offset + (i + 1) * X_SEGMENTS + j + 1);
            this->indices.push_back(offset + i * X_SEGMENTS + j + 1);
        }
    }
}