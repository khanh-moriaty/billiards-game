#include "stick.h"

Stick::Stick(glm::vec3 dir, float pow)
{
    this->direction = dir;
    this->power = pow;
}
Stick::Stick()
{
    this->direction = glm::vec3(1.f, 0.f, 1.f);
    this->power = 0.05f;
}