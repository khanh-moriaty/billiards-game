#pragma once

#include "game_object.h"

#include <glm/vec3.hpp>

class Ball : public GameObject
{
public:
    static const float RADIUS;
    static const float MASS;

private:

    int number;

    glm::vec3 velocity;
    glm::vec3 acceleration;

public:
    Ball(int number, Mesh* mesh);

    void update();

    int getNumber() { return this->number; }
};