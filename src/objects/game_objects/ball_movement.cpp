#include "ball_movement.h"

void BallMovement::update(float friction){
    this->velocity -= friction;
}

// glm::vec3 BallMovement::getVelocity(){
//     if (time <= 0) return glm::vec3(0.f);
//     glm::vec3 displacement = (1.0f * time / totalTime) * velocityVector;
//     return displacement;
// }