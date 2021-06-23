#pragma once

#include "game_object.h"
#include "stick.h"
#include "ball_movement.h"
#include <glm/vec3.hpp>

class Ball : public GameObject
{
public:
    static const float RADIUS;
    static const float MASS;
    //friction
    static const float ROLLING;
    static const float SLIDING;

private:

    int number;
    bool isMove;
    bool isInHole;
    std::vector<BallMovement*> ballMovements;

    glm::vec3 velocityVector;
    float RollingVelocity;
    float SlidingVelocity;

public:
    // Ball(int number, Mesh* mesh);
    Ball(int number, Mesh* mesh, glm::vec3 direction = glm::vec3(0.f), float power = 0.f);

    void update();
    void collide(GameObject* gameobj);
    bool inHole();

    void updateRolling();

    bool isHitBall(Ball* ball);
    void resifhitball(Ball* ball);

    int timeSliding(glm::vec3 velocity);
    int timeRolling(glm::vec3 velocity);

    void ballSliding();
    void ballRolling();
    void ballHitPool();

    void isBallInHole();

    glm::vec3 getRollingVelocity();
    glm::vec3 getSlidingVelocity();
    int getNumber() { return this->number; }
    bool isBall() {return true;}
};