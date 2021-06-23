#include "primitive.h"

const float Cone::TOP_RATIO = 0.1f;

int Cone::getXMax() {return 50;}
int Cone::getYMax() {return 50;}

Cone::Cone(float radius, float height)
{

    // Please refer to https://imgur.com/VuAhc5e for more insight

    top = TOP_RATIO * height; // top = p

    // (p^2 - R^2) * x^2 + 2hp^2 * x * + p^2(R^2 + h^2) = 0
    float delta = std::sqrt(4 * height * height * top * top * top * top - 4 * top * top * (top * top - radius * radius) * (radius * radius + height * height));
    float x = (-2 * height * top * top - delta) / 2 / (top * top - radius * radius);
    sphereRadius = (x + top) * (x + top) * x * radius * radius / (top * top * (x + height) * (x + height)) - x; // actually perimeter of the sphere
    sphereRadius = sphereRadius / 2;                                                                            // Now we have radius of the sphere
    float r = sphereRadius * sphereRadius / (x + sphereRadius);

    // fullHeight = (height - sphereRadius) + sphereRadius / (1 - TOP_RADIUS_RATIO);
    fullHeight = sphereRadius * sphereRadius / r + height - sphereRadius;

    this->radius = radius;
    this->height = height;

    initVertices();
    initIndices();
}

void Cone::getCoordinate()
{
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
}

void Cone::getNormalVector()
{
    if (ySegment <= 1 - TOP_RATIO)
    {
        float yLength = fullHeight * fullHeight * radius * radius / (fullHeight * fullHeight + radius * radius);
        float x = yLength * yLength / radius;
        normalVector = glm::normalize(glm::vec3(
            std::cos(xSegment * 2.0f * PI) * x,
            // fullHeight * fullHeight / (radius * radius),
            yLength * yLength / fullHeight,
            std::sin(xSegment * 2.0f * PI) * x));
    }
    else
    {
        normalVector = glm::normalize(glm::vec3(xPos, yPos - height + sphereRadius, zPos));
    }
}