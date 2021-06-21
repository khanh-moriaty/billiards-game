#include "ball.h"
#include <iostream>

const float RADIUS_HOLE = 0.075f;
const float namphanbay = 0.71428571428f;
const float Ball::RADIUS = 0.05f;
const float Ball::MASS = 1.f;
const float Ball::ROLLING = 0.01f;
const float Ball::SLIDING = 0.2f;

Ball::Ball(int number, Mesh *mesh, glm::vec3 direction, float power)
{
    this->number = number;
    this->mesh.push_back(mesh);
    this->mass = MASS;
    this->isMove = false;
    this->isInHole = false;
    if (glm::length(direction) == 0) {
        direction += glm::vec3(1e-5, 0, 1e-5);
    }
    this->velocityVector = glm::normalize(direction);
    this->RollingVelocity = namphanbay * power;
    this->SlidingVelocity = power;

}

bool Ball::inHole()
{
    return this->isInHole;
}
void Ball::update()
{   
    //std::cout<<(this->isInHole==true);
    this->isBallInHole();
    //std::cout<<"helo";
    this->ballHitPool();
    // Update velocity based on friction
    if(this->SlidingVelocity > this->RollingVelocity)
    {
        this->SlidingVelocity -= 9.8 * this->SLIDING / 240.f;
        this->ballSliding();
    }else{
        this->SlidingVelocity = -100.f; 
        this->RollingVelocity -= 9.8 * this->ROLLING / 240.f;
        if (this->RollingVelocity <= 0){
            this->RollingVelocity = 0.f;
        }
        this->ballRolling();
    }
}

glm::vec3 Ball::getRollingVelocity() {
    glm::vec3 velocity = this->RollingVelocity * this->velocityVector;
    return velocity;
}
glm::vec3 Ball::getSlidingVelocity() {
    glm::vec3 velocity = this->SlidingVelocity * this->velocityVector;
    return velocity;
}

bool Ball::isHitBall(Ball *ball)
{
    float dis = glm::length(this->mesh[0]->getPos() - ball->mesh[0]->getPos());
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

void Ball::ballSliding()
{
    glm::vec3 S = this->getSlidingVelocity();
    // this->mesh[0]->move(S);
    //std::cout<<"move";
}

void Ball::ballRolling()
{
    glm::vec3 S = this->getRollingVelocity();
    this->mesh[0]->move(S/2.f);
    this->mesh[0]->rotate(S/RADIUS);
}

void Ball::resifhitball(Ball* ball)
{
    if(Ball::isHitBall(ball) == true)
    {
        glm::vec3 velocity1 = this->getRollingVelocity();
        glm::vec3 velocity2 = ball->getRollingVelocity();
        
        float temp = glm::dot(velocity1 - velocity2, this->mesh[0]->getPos() - ball->mesh[0]->getPos());
        float dis = glm::length(this->mesh[0]->getPos() - ball->mesh[0]->getPos());

        glm::vec3 velocity = temp * (this->mesh[0]->getPos() - ball->mesh[0]->getPos())/(dis * dis);

        velocity1 -= velocity;
        if (glm::length(velocity1) == 0) {
            velocity1 += glm::vec3(1e-5, 0, 1e-5);
        }
        this->velocityVector = glm::normalize(velocity1);
        this->RollingVelocity = glm::length(velocity1);

        velocity2 += velocity;
        if (glm::length(velocity2) == 0) {
            velocity2 += glm::vec3(1e-5, 0, 1e-5);
        }
        ball->velocityVector = glm::normalize(velocity2);
        ball->RollingVelocity = glm::length(velocity2);
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
    //cham ben phai
    if(this->mesh[0]->getPos().x + RADIUS > 2){
        this->velocityVector.x = - this->velocityVector.x;
        // this->mesh[0]->setPosition(glm::vec3(2 - RADIUS,this->mesh[0]->getPos().y,this->mesh[0]->getPos().z));
        //std::cout<<"cham phai"<<std::endl;
    }else
    //cham ben trai
    if(this->mesh[0]->getPos().x - RADIUS < -2){
        this->velocityVector.x = - this->velocityVector.x;
        // this->mesh[0]->setPosition(glm::vec3(-2 + RADIUS,this->mesh[0]->getPos().y,this->mesh[0]->getPos().z));
        //std::cout<<"cham trai"<<std::endl;

    }
    //cham ben tren
    if(this->mesh[0]->getPos().z + RADIUS > 1){
        this->velocityVector.z = - this->velocityVector.z;
        // this->mesh[0]->setPosition(glm::vec3(this->mesh[0]->getPos().x,this->mesh[0]->getPos().y,1 - RADIUS));
        //std::cout<<"cham tren"<<std::endl;

    }else
    //cham ben duoi
    if(this->mesh[0]->getPos().z + RADIUS < -1){
        this->velocityVector.z = - this->velocityVector.z;
        // this->mesh[0]->setPosition(glm::vec3(this->mesh[0]->getPos().x,this->mesh[0]->getPos().y,-1 + RADIUS));
        //std::cout<<"cham duoi"<<std::endl;

    }
}

void Ball::isBallInHole()
{
    //lo phai tren
    if(glm::length(glm::vec2(this->mesh[0]->getPos().x,this->mesh[0]->getPos().z) - glm::vec2(2.f,1.f)) < RADIUS+RADIUS_HOLE){
        this->isInHole = true;
        this->RollingVelocity = 0.f;
        this->SlidingVelocity = 0.f;
    }else
    //lo giua tren
    if(glm::length(glm::vec2(this->mesh[0]->getPos().x,this->mesh[0]->getPos().z) - glm::vec2(0.f,1.f)) < RADIUS+RADIUS_HOLE){
        this->isInHole = true;
        this->RollingVelocity = 0.f;
        this->SlidingVelocity = 0.f;
    }else
    //lo trai tren
    if(glm::length(glm::vec2(this->mesh[0]->getPos().x,this->mesh[0]->getPos().z) - glm::vec2(-2.f,1.f)) < RADIUS+RADIUS_HOLE){
        this->isInHole = true;
        this->RollingVelocity = 0.f;
        this->SlidingVelocity = 0.f;
    }else
    //lo trai duoi
    if(glm::length(glm::vec2(this->mesh[0]->getPos().x,this->mesh[0]->getPos().z) - glm::vec2(-2.f,-1.f)) < RADIUS+RADIUS_HOLE){
        this->isInHole = true;
        this->RollingVelocity = 0.f;
        this->SlidingVelocity = 0.f;
    }else
    //lo giua duoi
    if(glm::length(glm::vec2(this->mesh[0]->getPos().x,this->mesh[0]->getPos().z) - glm::vec2(0.f,-1.f)) < RADIUS+RADIUS_HOLE){
        this->isInHole = true;
        this->RollingVelocity = 0.f;
        this->SlidingVelocity = 0.f;
    }else
    //lo phai duoi
    if(glm::length(glm::vec2(this->mesh[0]->getPos().x,this->mesh[0]->getPos().z) - glm::vec2(2.f,-1.f)) < RADIUS+RADIUS_HOLE){
        this->isInHole = true;
        this->RollingVelocity = 0.f;
        this->SlidingVelocity = 0.f;
    }
}