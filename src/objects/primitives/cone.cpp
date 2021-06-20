#include "primitive.h"

const int Cone::X_SEGMENTS = 50;
const int Cone::Y_SEGMENTS = 50;
const float Cone::TOP_RATIO = 0.1f;

#include <iostream>
Cone::Cone(float radius, float height)
{

    // Please refer to https://imgur.com/VuAhc5e for more insight

    top = TOP_RATIO * height;              // top = p

    // (p^2 - R^2) * x^2 + 2hp^2 * x * + p^2(R^2 + h^2) = 0
    float delta = std::sqrt(4 * height*height * top*top*top*top - 4 * top*top * (top*top - radius*radius) * (radius*radius + height*height));
    float x = (-2*height*top*top - delta) / 2 / (top*top - radius*radius);
    sphereRadius = (x+top)*(x+top) * x * radius * radius / (top*top * (x + height) * (x + height)) - x; // actually perimeter of the sphere
    sphereRadius = sphereRadius / 2; // Now we have radius of the sphere
    // sphereRadius = top / TOP_RADIUS_RATIO; // sphereRadius = (r+p)
    float r = sphereRadius * sphereRadius / (x + sphereRadius);

    // fullHeight = (height - sphereRadius) + sphereRadius / (1 - TOP_RADIUS_RATIO);
    fullHeight = sphereRadius * sphereRadius / r + height - sphereRadius;

    this->radius = radius;
    this->height = height;

    // outer layer
    generateConeLayer();
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

void Cone::generateConeLayer()
{
    for (int y = 0; y < Y_SEGMENTS; y++)
    {
        for (int x = 0; x < X_SEGMENTS; x++)
        {
            float xSegment = (float)x / (X_SEGMENTS - 1);
            float ySegment = (float)y / (Y_SEGMENTS - 1);
            float xPos, yPos, zPos;
            if (ySegment <= 1 - TOP_RATIO)
            {
                float tmpHeight = ySegment * height / fullHeight; // Generating cone based on fullHeight (cone height)
                xPos = std::cos(xSegment * 2.0f * PI) * (1 - tmpHeight) * radius;
                yPos = ySegment * height;
                zPos = std::sin(xSegment * 2.0f * PI) * (1 - tmpHeight) * radius;
            }
            else
            {
                // Generating sphere based on sphereRadius (sphere height)
                float tmpHeight = (ySegment * height - (height - sphereRadius)) / sphereRadius;
                // Radius of sphere at tmpHeight
                float tmpRadius = std::sqrt(1 - tmpHeight * tmpHeight) * sphereRadius;

                xPos = std::cos(xSegment * 2.0f * PI) * tmpRadius;
                yPos = tmpHeight * sphereRadius + height - sphereRadius;
                zPos = std::sin(xSegment * 2.0f * PI) * tmpRadius;
            }
            glm::vec3 pos = glm::vec3(xPos, yPos, zPos);
            glm::vec3 color = glm::vec3(0.f, 0.f, 0.f);
            glm::vec2 tex = glm::vec2(-xSegment, -ySegment);
            glm::vec3 nor;
            if (ySegment <= 1 - TOP_RATIO)
            {
                float yLength = fullHeight*fullHeight * radius*radius / (fullHeight*fullHeight + radius*radius);
                float x = yLength*yLength / radius;
                nor = glm::normalize(glm::vec3(
                    std::cos(xSegment * 2.0f * PI) * x,
                    // fullHeight * fullHeight / (radius * radius),
                    yLength*yLength / fullHeight,
                    std::sin(xSegment * 2.0f * PI) * x));
            }
            else
            {
                nor = glm::normalize(glm::vec3(xPos, yPos - height + sphereRadius, zPos));
            }
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