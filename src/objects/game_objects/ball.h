#pragma once

#include "game_object.h"
#include "stick.h"
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
    glm::vec3 veSliding; //include direction and power
    glm::vec3 veRolling;
    glm::vec3 acSliding;
    glm::vec3 acRolling;

public:
    Ball(int number, Mesh* mesh);

    void update();
    void collide(Ball* gameobj);
    void stickHitBall(glm::vec3 direction, float power);
    float timeSliding();
    float timeRolling();
    bool isHitBall(Ball* ball);
    void resifhitball(Ball* ball);
    void ballSliding();
    void ballRolling();
    void ballHitPool();
    void isBallInHole();
    int getNumber() { return this->number; }
};