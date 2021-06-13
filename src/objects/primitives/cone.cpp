#include "primitive.h"

const int Cone::X_SEGMENTS = 500;
const int Cone::Y_SEGMENTS = 2;

Cone::Cone(float radius, float height)
{
    // outer layer
    generateConeLayer(radius, height);
    generateIndices(0);
    // inner layer
    // generateConeLayer(radius * 0.95, height * 0.95, false);
    // generateIndices(X_SEGMENTS * Y_SEGMENTS);

    // // connect 2 layers together
    // for (int i = 0; i < X_SEGMENTS - 1; i++)
    // {
    //     this->indices.push_back(i);
    //     this->indices.push_back(i + 1);
    //     this->indices.push_back(X_SEGMENTS * Y_SEGMENTS + i + 1);
    //     this->indices.push_back(i);
    //     this->indices.push_back(X_SEGMENTS * Y_SEGMENTS + i);
    //     this->indices.push_back(X_SEGMENTS * Y_SEGMENTS + i + 1);
    // }
}

void Cone::generateConeLayer(float radius, float height, bool outer)
{
    for (int y = 0; y < Y_SEGMENTS; y++)
    {
        for (int x = 0; x < X_SEGMENTS; x++)
        {
            float xSegment = (float)x / (X_SEGMENTS - 1);
            float ySegment = (float)y / (Y_SEGMENTS - 1);
            float xPos = std::cos(xSegment * 2.0f * PI) * (1 - ySegment) * radius;
            float yPos = ySegment * height;
            float zPos = std::sin(xSegment * 2.0f * PI) * (1 - ySegment) * radius;
            glm::vec3 pos = glm::vec3(xPos, yPos, zPos);
            glm::vec3 color = glm::vec3(0.f, 0.f, 0.f);
            glm::vec2 tex = glm::vec2(-xSegment, -ySegment);
            if (!outer)
                outer = -1;
            glm::vec3 nor = glm::normalize(glm::vec3(
                                        outer * std::cos(xSegment * 2.0f * PI),
                                        outer * height * height / (radius * radius),
                                        outer * std::sin(xSegment * 2.0f * PI)));
            Vertex temp;
            temp.position = pos;
            temp.color = color;
            temp.texcoord = tex;
            temp.normal = nor;
            this->vertices.push_back(temp);
        }
    }
}

void Cone::generateIndices(int offset)
{
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