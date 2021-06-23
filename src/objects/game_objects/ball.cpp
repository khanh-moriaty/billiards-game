#include "ball.h"
#include <iostream>

const float RADIUS_HOLE = 0.075f;
const float namphanbay = 0.71428571428f;
const float Ball::RADIUS = 0.05f;
const float Ball::MASS = 1.f;
const float Ball::ROLLING = 0.07f;
const float Ball::SLIDING = 0.7f;
const float dt = 0.00833333333f;
void xuat(glm::vec3 a)
{
    std::cout<<a.x<<" "<<a.y<<" "<<a.z<<std::endl;
}
Ball::Ball(int number, Mesh *mesh, glm::vec3 direction, float power)
{
    this->number = number;
    this->mesh.push_back(mesh);
    this->mass = MASS;
    this->isMove = false;
    this->isInHole = false;
    if (glm::length(direction) == 0.f) {
        this->velocityVector = glm::vec3(0.f);
    }
    else this->velocityVector = glm::normalize(direction);
    this->RollingVelocity = namphanbay * power;
    this->SlidingVelocity = power;

}

bool Ball::inHole()
{
    return this->isInHole;
}
void Ball::update()
{      
    this->isBallInHole();
    if(!this->isInHole && glm::length(this->velocityVector)!=0)
    {   
        // Update velocity based on friction
        if(this->SlidingVelocity > this->RollingVelocity)
        {
            float v = this->SlidingVelocity;
            float a = 9.8 * this->SLIDING;
            float s = v*dt - 0.5f*a*dt*dt;
            float len = glm::length(this->velocityVector);
            glm::vec3 dis = this->velocityVector * s/len;
            this->mesh[0]->move(dis);
            this->SlidingVelocity -= 9.8 * this->SLIDING * dt;
            if(this->SlidingVelocity<=0)
                this->SlidingVelocity = 0.f; 
            //this->ballSliding();
        }else
        if(this->RollingVelocity>0){
            float v = this->RollingVelocity;
            float a = 9.8 * this->ROLLING;
            float s = v*dt - 0.5f*a*dt*dt;
            float len = glm::length(this->velocityVector);
            glm::vec3 dis = this->velocityVector * s/len;
            this->mesh[0]->rotate(dis/RADIUS);
            this->mesh[0]->move(dis);
            this->RollingVelocity -= 9.8 * this->ROLLING *dt;
            if (this->RollingVelocity <= 0){
                this->RollingVelocity = 0.f;
            }
            //this->ballRolling();
        }
        this->ballHitPool();
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
    if(dis < 2*RADIUS-(1e-5))
        return true;
    return false;
}

// float Ball::timeSliding()
// {
//     return (2 * glm::length(this->veSliding))/(7 * 9.8 * this->SLIDING);
// }

void Ball::ballSliding()
{
    glm::vec3 S = this->getSlidingVelocity();
    this->mesh[0]->move(S);
}

void Ball::ballRolling()
{
    glm::vec3 S = this->getRollingVelocity();
    this->mesh[0]->move(S);
    this->mesh[0]->rotate(S/RADIUS);
}

void Ball::resifhitball(Ball* ball)
{
    if(Ball::isHitBall(ball) == true)
    {
        glm::vec3 velocity1 = this->velocityVector * this->RollingVelocity;
        glm::vec3 velocity2 = ball->velocityVector * ball->RollingVelocity;

        float temp = glm::dot(velocity1 - velocity2, this->mesh[0]->getPos() - ball->mesh[0]->getPos());
        float dis = glm::length(this->mesh[0]->getPos() - ball->mesh[0]->getPos());
        
        glm::vec3 velocity = temp * (this->mesh[0]->getPos() - ball->mesh[0]->getPos())/(dis * dis);

        velocity1 -= velocity;
        if (glm::length(velocity1) == 0) {
            this->velocityVector = glm::vec3(0.f);
            this->RollingVelocity = 0.f;
        }else{
            this->velocityVector = glm::normalize(velocity1);
            this->RollingVelocity = glm::length(velocity1);
        }
        velocity2 += velocity;
        if (glm::length(velocity2) == 0) {
            ball->velocityVector = glm::vec3(0.f);
            ball->RollingVelocity = 0.f;
            
        }else{
            ball->RollingVelocity = glm::length(velocity2);
            ball->velocityVector = glm::normalize(velocity2);
        }
        
        this->update();
        ball->update();
        if(this->isHitBall(ball)){
            glm::vec3 dirCenter = this->mesh[0]->getPos()-ball->mesh[0]->getPos();
            temp = RADIUS - dis;
            this->mesh[0]->setPosition(glm::vec3(this->mesh[0]->getPos()-glm::normalize(dirCenter)*temp));
            ball->mesh[0]->setPosition(glm::vec3(ball->mesh[0]->getPos()+glm::normalize(dirCenter)*temp));  
        }    
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
    if(this->mesh[0]->getPos().x + RADIUS > 1.32f){
        this->velocityVector.x = - this->velocityVector.x;
        this->mesh[0]->setPosition(glm::vec3(1.32f - RADIUS,this->mesh[0]->getPos().y,this->mesh[0]->getPos().z));
        //std::cout<<"cham phai"<<std::endl;
    }else
    //cham ben trai
    if(this->mesh[0]->getPos().x - RADIUS < -2.12f){
        this->velocityVector.x = - this->velocityVector.x;
        this->mesh[0]->setPosition(glm::vec3(-2.12f + RADIUS,this->mesh[0]->getPos().y,this->mesh[0]->getPos().z));
        //std::cout<<"cham trai"<<std::endl;

    }
    //cham ben tren
    if(this->mesh[0]->getPos().z + RADIUS > 0.87f){
        this->velocityVector.z = - this->velocityVector.z;
        this->mesh[0]->setPosition(glm::vec3(this->mesh[0]->getPos().x,this->mesh[0]->getPos().y,0.87f - RADIUS));
        //std::cout<<"cham tren"<<std::endl;

    }else
    //cham ben duoi
    if(this->mesh[0]->getPos().z - RADIUS < -0.76f){
        this->velocityVector.z = - this->velocityVector.z;
        this->mesh[0]->setPosition(glm::vec3(this->mesh[0]->getPos().x,this->mesh[0]->getPos().y,-0.76f + RADIUS));
        //std::cout<<"cham duoi"<<std::endl;

    }
}

void Ball::isBallInHole()
{
    //lo phai tren
    if(glm::length(glm::vec2(this->mesh[0]->getPos().x,this->mesh[0]->getPos().z) - glm::vec2(1.3f,0.85f)) < RADIUS_HOLE){
        this->isInHole = true;
        this->RollingVelocity = 0.f;
        this->SlidingVelocity = 0.f;
    }else
    //lo giua tren
    if(glm::length(glm::vec2(this->mesh[0]->getPos().x,this->mesh[0]->getPos().z) - glm::vec2(-0.42f,0.85f)) < RADIUS_HOLE){
        this->isInHole = true;
        this->RollingVelocity = 0.f;
        this->SlidingVelocity = 0.f;
    }else
    //lo trai tren
    if(glm::length(glm::vec2(this->mesh[0]->getPos().x,this->mesh[0]->getPos().z) - glm::vec2(-2.1f,0.85f)) < RADIUS_HOLE){
        this->isInHole = true;
        this->RollingVelocity = 0.f;
        this->SlidingVelocity = 0.f;
    }else
    //lo trai duoi
    if(glm::length(glm::vec2(this->mesh[0]->getPos().x,this->mesh[0]->getPos().z) - glm::vec2(-2.1f,-0.74f)) < RADIUS_HOLE){
        this->isInHole = true;
        this->RollingVelocity = 0.f;
        this->SlidingVelocity = 0.f;
    }else
    //lo giua duoi
    if(glm::length(glm::vec2(this->mesh[0]->getPos().x,this->mesh[0]->getPos().z) - glm::vec2(-0.42f,-0.74f)) < RADIUS_HOLE){
        this->isInHole = true;
        this->RollingVelocity = 0.f;
        this->SlidingVelocity = 0.f;
    }else
    //lo phai duoi
    if(glm::length(glm::vec2(this->mesh[0]->getPos().x,this->mesh[0]->getPos().z) - glm::vec2(1.3f,-0.74f)) < RADIUS_HOLE){
        this->isInHole = true;
        this->RollingVelocity = 0.f;
        this->SlidingVelocity = 0.f;
    }
}