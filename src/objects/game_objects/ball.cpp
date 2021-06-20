#include "ball.h"

const float Ball::RADIUS = 0.05f;
const float Ball::MASS = 1.f;

Ball::Ball(int number, Mesh *mesh)
{
    this->mesh.push_back(mesh);
    this->mass = MASS;
    this->velocity = glm::vec3(0.f);
    this->acceleration = glm::vec3(0.f);
}

void Ball::update()
{
    // const float v = -0.0005f;

    // glm::vec3 v1 = glm::vec3(v, 0.f, 0.f);
    // glm::vec3 v2 = glm::vec3(0.f, 0.f, 0.6*v);
    // this->mesh->move(v1);
    // this->mesh->move(v2);

    // glm::vec3 r = (v1+v2) / RADIUS;
    // this->mesh->rotate(r);
}