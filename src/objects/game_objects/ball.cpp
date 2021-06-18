#include "ball.h"
const float RADIUS_HOLE = 0.075f;
const float namphanbay = 0.71428571428f;
const float Ball::RADIUS = 0.05f;
const float Ball::MASS = 1.f;
const float Ball::ROLLING = 0.01f;
const float Ball::SLIDING = 0.2f;

Ball::Ball(int number, Mesh *mesh)
{
    this->mesh = mesh;
    this->mass = MASS;
    bool isMove = false;
    bool isInHole = false;
    this->veSliding = glm::vec3(0.f);
    this->veRolling = glm::vec3(0.f);
    this->acSliding = glm::vec3(0.f);
    this->acRolling = glm::vec3(0.f);
}
#include <iostream>
void Ball::update()
{   
    this->ballHitPool();
    this->isBallInHole();
    //this->mesh->move(glm::vec3(1.f,0.f,1.f)*0.005f);
    // const float v = -0.0005f;

    // glm::vec3 v1 = glm::vec3(v, 0.f, 0.f);
    // glm::vec3 v2 = glm::vec3(0.f, 0.f, 0.6*v);
    // this->mesh->move(v1+v2);

    // glm::vec3 r = (v1+v2) / RADIUS;
    // this->mesh->rotate(r);
}
bool Ball::isHitBall(Ball *ball)
{
    float dis = glm::length(this->mesh->getPos() - ball->mesh->getPos());
    if(dis < 2*RADIUS)
        return true;
    return false;
}
void Ball::stickHitBall(glm::vec3 direction, float power)
{
    this->veSliding = direction * power;    
}
float Ball::timeSliding()
{
    return (2 * glm::length(this->veSliding))/(7 * 9.8 * this->SLIDING);
}
void Ball::ballSliding()
{
    float t = this->timeSliding();
    this->veRolling = this->veSliding * namphanbay;
    this->acSliding = - this->veSliding * (1 - namphanbay) / t;
    //glm::vec3 S = this->veSliding * t + this->acSliding * t * t * 0.5f;
    //this->mesh->move(S);
}
float Ball::timeRolling()
{
    return (2 * glm::length(this->veRolling))/(9.8 * this->ROLLING);
}
void Ball::ballRolling()
{
    float t = this->timeRolling();
    this->acRolling = - this->veRolling / t;
    //glm::vec3 S = this->veRolling * t + this->acRolling * t * t * 0.5f;
    //this->mesh->move(S);
    //this->mesh->rotate(S/RADIUS);
}
void Ball::resifhitball(Ball* ball)
{
    if(Ball::isHitBall(ball) == true)
    {
        float temp = glm::dot(this->veRolling - ball->veRolling, this->mesh->getPos() - ball->mesh->getPos());
        float dis = glm::length(this->mesh->getPos() - ball->mesh->getPos());
        this->veRolling = this->veRolling - temp * (this->mesh->getPos() - ball->mesh->getPos())/(dis * dis);
        ball->veRolling = ball->veRolling + temp * (this->mesh->getPos() - ball->mesh->getPos())/(dis * dis);
    }
}
void Ball::collide(Ball* gameobj)
{
    this->resifhitball(gameobj);
}

void Ball::ballHitPool()
{
    //ban co 8x4
    //cham ben phai
    if(this->mesh->getPos().x + RADIUS > 4){
        this->veRolling.x = - this->veRolling.x;
        this->mesh->setPosition(glm::vec3(4 - RADIUS,this->mesh->getPos().y,this->mesh->getPos().z));
    }else
    //cham ben trai
    if(this->mesh->getPos().x - RADIUS < -4){
        this->veRolling.x = - this->veRolling.x;
        this->mesh->setPosition(glm::vec3(-4 + RADIUS,this->mesh->getPos().y,this->mesh->getPos().z));
    }
    //cham ben tren
    if(this->mesh->getPos().z + RADIUS > 2){
        this->veRolling.z = - this->veRolling.z;
        this->mesh->setPosition(glm::vec3(this->mesh->getPos().x,this->mesh->getPos().y,2 - RADIUS));
    }else
    //cham ben duoi
    if(this->mesh->getPos().z + RADIUS < -2){
        this->veRolling.z = - this->veRolling.z;
        this->mesh->setPosition(glm::vec3(this->mesh->getPos().x,this->mesh->getPos().y,-2 + RADIUS));
    }
}
void Ball::isBallInHole()
{
    //lo phai tren
    if(glm::length(glm::vec2(this->mesh->getPos().x,this->mesh->getPos().z) - glm::vec2(4,2)) < RADIUS+RADIUS_HOLE){
        this->isInHole = true;
    }else
    //lo giua tren
    if(glm::length(glm::vec2(this->mesh->getPos().x,this->mesh->getPos().z) - glm::vec2(0,2)) < RADIUS+RADIUS_HOLE){
        this->isInHole = true;
    }else
    //lo trai tren
    if(glm::length(glm::vec2(this->mesh->getPos().x,this->mesh->getPos().z) - glm::vec2(-4,2)) < RADIUS+RADIUS_HOLE){
        this->isInHole = true;
    }else
    //lo trai duoi
    if(glm::length(glm::vec2(this->mesh->getPos().x,this->mesh->getPos().z) - glm::vec2(-4,-2)) < RADIUS+RADIUS_HOLE){
        this->isInHole = true;
    }else
    //lo giua duoi
    if(glm::length(glm::vec2(this->mesh->getPos().x,this->mesh->getPos().z) - glm::vec2(0,-2)) < RADIUS+RADIUS_HOLE){
        this->isInHole = true;
    }else
    //lo phai duoi
    if(glm::length(glm::vec2(this->mesh->getPos().x,this->mesh->getPos().z) - glm::vec2(4,-2)) < RADIUS+RADIUS_HOLE){
        this->isInHole = true;
    }
}