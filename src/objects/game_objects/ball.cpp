#include "ball.h"
#include <iostream>

const float RADIUS_HOLE = 0.075f;
const float namphanbay = 0.71428571428f;
const float Ball::RADIUS = 0.05f;
const float Ball::MASS = 1.f;
const float Ball::ROLLING = 0.01f;
const float Ball::SLIDING = 0.2f;

Ball::Ball(int number, Mesh *mesh, glm::vec3 velRolling)
{
    this->mesh = mesh;
    this->mass = MASS;
    bool isMove = false;
    bool isInHole = false;
    // this->ballMovements.push_back(new BallMovement(velRolling, 60));
    if (glm::length(velRolling) == 0) {
        velRolling += glm::vec3(1e-5);
    }
    this->velocityVector = glm::normalize(velRolling);
    this->velocity = glm::length(velRolling);
}

void Ball::update()
{   
    this->ballHitPool();
    // this->isBallInHole();

    // Update velocity vectors
    // for (auto x: this->ballMovements){
    //     x->update();
    // }

    // Update velocity based on friction
    this->velocity -= 9.8 * this->ROLLING / 240.f;
    if (this->velocity <= 0){
        this->velocity = 0.f;
    }

    // Update ball position based on rolling velocity
    this->ballRolling();

    //this->mesh->move(glm::vec3(1.f,0.f,1.f)*0.005f);
    // const float v = -0.0005f;

    // glm::vec3 v1 = glm::vec3(v, 0.f, 0.f);
    // glm::vec3 v2 = glm::vec3(0.f, 0.f, 0.6*v);
    // this->mesh->move(v1+v2);

    // glm::vec3 r = (v1+v2) / RADIUS;
    // this->mesh->rotate(r);
}

glm::vec3 Ball::getVelocity() {
    // glm::vec3 velocity(0.f);
    // for (auto x: this->ballMovements){
    //     velocity += x->getVelocity();
    // }
    glm::vec3 velocity = this->velocity * this->velocityVector;
    return velocity;
}

bool Ball::isHitBall(Ball *ball)
{
    float dis = glm::length(this->mesh->getPos() - ball->mesh->getPos());
    if(dis < 2*RADIUS)
        return true;
    return false;
}

// void Ball::stickHitBall(glm::vec3 direction, float power)
// {
//     this->veSliding = direction * power;    
// }

// float Ball::timeSliding()
// {
//     return (2 * glm::length(this->veSliding))/(7 * 9.8 * this->SLIDING);
// }

// void Ball::ballSliding()
// {
//     float t = this->timeSliding();
//     this->veRolling = this->veSliding * namphanbay;
//     this->acSliding = - this->veSliding * (1 - namphanbay) / t;
//     //glm::vec3 S = this->veSliding * t + this->acSliding * t * t * 0.5f;
//     //this->mesh->move(S);
// }

void Ball::ballRolling()
{
    glm::vec3 S = this->getVelocity();
    this->mesh->move(S);
    this->mesh->rotate(S/RADIUS);
}

void Ball::resifhitball(Ball* ball)
{
    if(Ball::isHitBall(ball) == true)
    {
        glm::vec3 velocity1 = this->getVelocity();
        glm::vec3 velocity2 = ball->getVelocity();
        
        float temp = glm::dot(velocity1 - velocity2, this->mesh->getPos() - ball->mesh->getPos());
        float dis = glm::length(this->mesh->getPos() - ball->mesh->getPos());

        glm::vec3 velocity = temp * (this->mesh->getPos() - ball->mesh->getPos())/(dis * dis);

        velocity1 -= velocity;
        if (glm::length(velocity1) == 0) {
            velocity1 += glm::vec3(1e-5);
        }
        this->velocityVector = glm::normalize(velocity1);
        this->velocity = glm::length(velocity1);

        velocity2 += velocity;
        if (glm::length(velocity2) == 0) {
            velocity2 += glm::vec3(1e-5);
        }
        ball->velocityVector = glm::normalize(velocity2);
        ball->velocity = glm::length(velocity2);
    }
}

void Ball::collide(GameObject* gameobj)
{
    if (!gameobj->isBall()) return;
    Ball* ball = (Ball*) gameobj;
    this->resifhitball(ball);
}

void Ball::ballHitPool()
{
    //ban co 8x4
    //cham ben phai
    if(this->mesh->getPos().x + RADIUS > 2){
        this->velocityVector.x = - this->velocityVector.x;
        this->mesh->setPosition(glm::vec3(2 - RADIUS,this->mesh->getPos().y,this->mesh->getPos().z));
    }else
    //cham ben trai
    if(this->mesh->getPos().x - RADIUS < -2){
        this->velocityVector.x = - this->velocityVector.x;
        this->mesh->setPosition(glm::vec3(-2 + RADIUS,this->mesh->getPos().y,this->mesh->getPos().z));
    }
    //cham ben tren
    if(this->mesh->getPos().z + RADIUS > 1){
        this->velocityVector.z = - this->velocityVector.z;
        this->mesh->setPosition(glm::vec3(this->mesh->getPos().x,this->mesh->getPos().y,1 - RADIUS));
    }else
    //cham ben duoi
    if(this->mesh->getPos().z + RADIUS < -1){
        this->velocityVector.z = - this->velocityVector.z;
        this->mesh->setPosition(glm::vec3(this->mesh->getPos().x,this->mesh->getPos().y,-1 + RADIUS));
    }
}

// void Ball::isBallInHole()
// {
//     //lo phai tren
//     if(glm::length(glm::vec2(this->mesh->getPos().x,this->mesh->getPos().z) - glm::vec2(4,2)) < RADIUS+RADIUS_HOLE){
//         this->isInHole = true;
//     }else
//     //lo giua tren
//     if(glm::length(glm::vec2(this->mesh->getPos().x,this->mesh->getPos().z) - glm::vec2(0,2)) < RADIUS+RADIUS_HOLE){
//         this->isInHole = true;
//     }else
//     //lo trai tren
//     if(glm::length(glm::vec2(this->mesh->getPos().x,this->mesh->getPos().z) - glm::vec2(-4,2)) < RADIUS+RADIUS_HOLE){
//         this->isInHole = true;
//     }else
//     //lo trai duoi
//     if(glm::length(glm::vec2(this->mesh->getPos().x,this->mesh->getPos().z) - glm::vec2(-4,-2)) < RADIUS+RADIUS_HOLE){
//         this->isInHole = true;
//     }else
//     //lo giua duoi
//     if(glm::length(glm::vec2(this->mesh->getPos().x,this->mesh->getPos().z) - glm::vec2(0,-2)) < RADIUS+RADIUS_HOLE){
//         this->isInHole = true;
//     }else
//     //lo phai duoi
//     if(glm::length(glm::vec2(this->mesh->getPos().x,this->mesh->getPos().z) - glm::vec2(4,-2)) < RADIUS+RADIUS_HOLE){
//         this->isInHole = true;
//     }
// }