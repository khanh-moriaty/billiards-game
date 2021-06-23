#pragma once

#include <glm/vec3.hpp>

class BallMovement {
private:
    glm::vec3 velocityVector;
    glm::vec3 velocity;
public:

    BallMovement(glm::vec3 velocityVector = glm::vec3(0.f), float velocity = 0.f):
        velocityVector(velocityVector), velocity(velocity) {}

    void update(float friction);
    glm::vec3 getVelocity() {return this->velocity * this->velocityVector;}

};