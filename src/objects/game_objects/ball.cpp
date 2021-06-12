#include "ball.h"

const float Ball::RADIUS = 0.05f;
const float Ball::MASS = 1.f;

Ball::Ball(int number, Mesh *mesh)
{
    this->mesh = mesh;
    this->mass = MASS;
    this->velocity = glm::vec3(0.f);
    this->acceleration = glm::vec3(0.f);
}

#include <stdio.h>
void Ball::update()
{
}